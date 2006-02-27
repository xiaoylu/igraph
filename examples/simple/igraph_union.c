
#include <igraph.h>

#include <stdlib.h>
#include <stdio.h>

int print_vector(igraph_vector_t *v) {
  long int i, l=igraph_vector_size(v);
  for (i=0; i<l; i++) {
    printf(" %li", (long int) VECTOR(*v)[i]);
  }
  printf("\n");
}

int main() {
  
  igraph_t left, right, uni;
  igraph_vector_t v;
  igraph_vector_ptr_t glist;
  long int i;

  igraph_vector_init_int_end(&v, -1, 0,1, 1,2, 2,2, 2,3, -1);
  igraph_create(&left, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  
  igraph_vector_init_int_end(&v, -1, 0,1, 1,2, 2,2, 2,4, -1); 
  igraph_create(&right, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  
  igraph_union(&uni, &left, &right);
  igraph_write_graph_edgelist(&uni, stdout);

  igraph_destroy(&uni);
  igraph_destroy(&left);
  igraph_destroy(&right);

  /* Empty graph list */
  igraph_vector_ptr_init(&glist, 0);
  igraph_union_many(&uni, &glist);
  if (!igraph_is_directed(&uni) || igraph_vcount(&uni) != 0) {
    return 1;
  }
  igraph_vector_ptr_destroy(&glist);
  igraph_destroy(&uni);  

  /* Non-empty graph list */
  igraph_vector_ptr_init(&glist, 10); 
  for (i=0; i<igraph_vector_ptr_size(&glist); i++) {
    VECTOR(glist)[i]=calloc(1, sizeof(igraph_t));
    igraph_vector_init_int_end(&v, -1, 0,1, 1,0, -1);
    igraph_create(VECTOR(glist)[i], &v, 0, IGRAPH_DIRECTED);    
    igraph_vector_destroy(&v);
  }

  igraph_union_many(&uni, &glist);
  igraph_write_graph_edgelist(&uni, stdout);

  for (i=0; i<igraph_vector_ptr_size(&glist); i++) {
    igraph_destroy(VECTOR(glist)[i]);
    free(VECTOR(glist)[i]);
  }
  igraph_vector_ptr_destroy(&glist);
  igraph_destroy(&uni);  

  /* Another non-empty graph list */
  igraph_vector_ptr_init(&glist, 10); 
  for (i=0; i<igraph_vector_ptr_size(&glist); i++) {
    VECTOR(glist)[i]=calloc(1, sizeof(igraph_t));
    igraph_vector_init_int_end(&v, -1, i,i+1, 1,0, -1);
    igraph_create(VECTOR(glist)[i], &v, 0, IGRAPH_DIRECTED);    
    igraph_vector_destroy(&v);
  }

  igraph_union_many(&uni, &glist);
  igraph_write_graph_edgelist(&uni, stdout);

  for (i=0; i<igraph_vector_ptr_size(&glist); i++) {
    igraph_destroy(VECTOR(glist)[i]);
    free(VECTOR(glist)[i]);
  }
  igraph_vector_ptr_destroy(&glist);
  igraph_destroy(&uni);  
  
  /* Undirected graph list*/
  igraph_vector_ptr_init(&glist, 10); 
  for (i=0; i<igraph_vector_ptr_size(&glist); i++) {
    VECTOR(glist)[i]=calloc(1, sizeof(igraph_t));
    igraph_vector_init_int_end(&v, -1, i,i+1, 1,0, -1);
    igraph_create(VECTOR(glist)[i], &v, 0, IGRAPH_UNDIRECTED);    
    igraph_vector_destroy(&v);
  }

  igraph_union_many(&uni, &glist);
  igraph_write_graph_edgelist(&uni, stdout);

  for (i=0; i<igraph_vector_ptr_size(&glist); i++) {
    igraph_destroy(VECTOR(glist)[i]);
    free(VECTOR(glist)[i]);
  }
  igraph_vector_ptr_destroy(&glist);
  igraph_destroy(&uni);  

  return 0;
}
