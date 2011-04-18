/** 
 * @file: LEdge.cpp
 */

#include "Layout.h"

void LEdge::BreakLongEdge(){
	
	///Difference between rank of the "in" and "out"  nodes
        int n = ((pLNode) to())->Rank() - ((pLNode) from())->Rank();

        list<pLEdge> *edges_list = new list<pLEdge>;

        pLNode prevnode = ((pLNode) from());
        pLNode newnode;

        bool is_reverse = reverse;
        pEdge new_edge;
        ///Adding n-1 nodes to do all rank differences equal 1
        for (int i = 1; i < n; i++){
               newnode = (pLNode) graph()->AddNode();
		newnode->dummy = true;
		newnode->rank = (((pLNode) from())->Rank()) + i;
                new_edge = graph()->AddEdge(prevnode, newnode);
                new_edge->SetReverse(is_reverse);
                edges_list->push_back((pLEdge) new_edge);
		prevnode = newnode;
        }
        new_edge = graph()->AddEdge(prevnode, to());
        new_edge->SetReverse(is_reverse);
        edges_list->push_back((pLEdge) new_edge);
        graph()->DeleteEdge(from(), to());
        ((pLGraph) graph())->long_edges_list()->push_back(edges_list);

        for(list<pLEdge>::iterator edge_iter = edges_list->begin();
            edge_iter != edges_list->end();
            edge_iter++){
                ( (pLEdge) *edge_iter)->m_composite_edges = edges_list;
            }
}

void LEdge::CompositeEdgesDump(){
    printf("Edge: %d. Composite Edges:\n",id());
    if (m_composite_edges != NULL){
        for(list<pLEdge>::iterator edge_iter = m_composite_edges->begin();
            edge_iter != m_composite_edges->end();
            edge_iter++){
                printf("%d   ", (*edge_iter)->id());
           }
    }
    printf("\n");
}
