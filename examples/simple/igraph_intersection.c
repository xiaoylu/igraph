
#include <igraph.h>

int print_vector(igraph_vector_t *v) {
  long int i, l=igraph_vector_size(v);
  for (i=0; i<l; i++) {
    printf(" %li", (long int) VECTOR(*v)[i]);
  }
  printf("\n");
}

int main() {

  igraph_t left, right, isec;
  igraph_vector_t v;
  igraph_vector_ptr_t glist;
  igraph_t g1, g2, g3;

  igraph_vector_init_int_end(&v, -1, 0,1, 1,2, 2,3, -1);
  igraph_create(&left, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);

  igraph_vector_init_int_end(&v, -1, 1,0, 5,4, 1,2, 3,2, -1);
  igraph_create(&right, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  
  igraph_intersection(&isec, &left, &right);
  igraph_vector_init(&v, 0);
  igraph_get_edgelist(&isec, &v, 0);
  print_vector(&v);
  igraph_vector_destroy(&v);
  igraph_destroy(&left);
  igraph_destroy(&right);
  igraph_destroy(&isec);    

  /* empty graph list */
  igraph_vector_ptr_init(&glist, 0);
  igraph_intersection_many(&isec, &glist);
  if (igraph_vcount(&isec) != 0 || !igraph_is_directed(&isec)) {
    return 1;
  }
  igraph_destroy(&isec);
  igraph_vector_ptr_destroy(&glist);

  /* graph list with an empty graph */
  igraph_vector_ptr_init(&glist, 3);
  igraph_vector_init_int_end(&v, -1, 0,1, 1,2, 2,3, -1);
  igraph_create(&g1, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  igraph_vector_init_int_end(&v, -1, 0,1, 1,2, 2,3, -1);
  igraph_create(&g2, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  igraph_empty(&g3, 10, IGRAPH_DIRECTED);

  VECTOR(glist)[0]=&g1;
  VECTOR(glist)[1]=&g2;
  VECTOR(glist)[2]=&g3;
  igraph_intersection_many(&isec, &glist);
  if (igraph_ecount(&isec) != 0 || igraph_vcount(&isec) != 10) {
    return 2;
  }
  igraph_destroy(&g1);
  igraph_destroy(&g2);
  igraph_destroy(&g3);
  igraph_destroy(&isec);
  igraph_vector_ptr_destroy(&glist);
  
  /* "proper" graph list */
  igraph_vector_ptr_init(&glist, 3);
  igraph_vector_init_int_end(&v, -1, 0,1, 1,2, 2,3, -1);
  igraph_create(&g1, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  igraph_vector_init_int_end(&v, -1, 0,1, 1,2, 2,3, 3,2, 4,5, 6,5, -1);
  igraph_create(&g2, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  igraph_vector_init_int_end(&v, -1, 2,3, 1,0, 1,2, 3,2, 4,5, 6,5, 2,3, -1);
  igraph_create(&g3, &v, 0, IGRAPH_DIRECTED);
  igraph_vector_destroy(&v);
  
  VECTOR(glist)[0]=&g1;
  VECTOR(glist)[1]=&g2;
  VECTOR(glist)[2]=&g3;
  igraph_intersection_many(&isec, &glist);
  igraph_write_graph_edgelist(&isec, stdout);
  igraph_destroy(&g1);
  igraph_destroy(&g2);
  igraph_destroy(&g3);
  igraph_destroy(&isec);
  igraph_vector_ptr_destroy(&glist);

  return 0;
}
