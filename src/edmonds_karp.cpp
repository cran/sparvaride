/*
 * R package sparvaride by
 *     Darjus Hosszejni and Sylvia Frühwirth-Schnatter Copyright (C) 2023-
 *
 *  This file is part of the R package sparvaride: Variance Identification
 *  in Sparse Factor Analysis
 *
 *  The R package sparvaride is free software: you can redistribute it
 *  and/or modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 2 or
 *  any later version of the License.
 *
 *  The R package sparvaride is distributed in the hope that it will be
 *  useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the R package sparvaride. If that is not the case, please
 *  refer to <http://www.gnu.org/licenses/>.
 */


#include <RcppArmadillo.h>
#include <limits>
#include <queue>
#include <vector>
#include "edmonds_karp.h"

unsigned int edmonds_karp (
    Graph& graph) {
  const Vertex source = 0;
  const Vertex target = graph.size() - 1;
  int flow = 0;
  while (true) {
    std::vector<Edge*> predecessor (graph.size());  // store edge taken to get to a vertex
    std::fill(predecessor.begin(), predecessor.end(), nullptr);
    // run a breadth-first search to findthe shortest s-t path
    std::queue<Vertex> q;
    q.push(0);
    while (not q.empty()) {
      const Vertex current = q.front();
      q.pop();
      for (Edge& edge : graph[current]) {
        if (predecessor[edge.end] == nullptr and
            edge.end != source and
            edge.capacity > edge.flow) {
          predecessor[edge.end] = &edge;
          q.push(edge.end);
        }
      }
    }

    if (predecessor[target] != nullptr) {
      // we found an augmenting path
      // see how much from we can send
      int df = std::numeric_limits<int>::max();
      for (Edge* edge_ptr = predecessor[target]; edge_ptr != nullptr; edge_ptr = predecessor[edge_ptr -> start]) {
        df = std::min(df, (edge_ptr -> capacity) - (edge_ptr -> flow));
      }
      // update edges by that amount
      for (Edge* edge_ptr = predecessor[target]; edge_ptr != nullptr; edge_ptr = predecessor[edge_ptr -> start]) {
        edge_ptr -> flow += df;
        edge_ptr -> reverse -> flow -= df;
      }
      flow += df;
    } else {
      break;
    }
  }

  return flow;
}

