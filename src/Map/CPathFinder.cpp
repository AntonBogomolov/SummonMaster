#include "CPathFinder.h"

#include <unordered_map>
#include "CMap.h"


CPathFinder::CPathFinder(const CMap* map) : map(map)
{
    if(this->map)
    {
        this->width  = this->map->getWidth();
        this->height = this->map->getHeight();
    }
    else
    {
        this->width  = 0;
        this->height = 0;
    }
}

CPathFinderAStar::CPathFinderAStar(const CMap* map) : CPathFinder(map)
{
    
}   
   
CPathOnMap CPathFinderAStar::findPath(const CCellCoords& start, const CCellCoords& end, const CMovableObject* object) const
{
    CPathOnMap resultPath;
    CPathNode startNode(start.row, start.col);
    CPathNode endNode(end.row, end.col);
    
    std::unordered_map<long ,long> costs;
    std::priority_queue<CPathNode> nodesToVisit;
    costs[startNode.getFlatIndex(width)] = 0;
    nodesToVisit.push(startNode);
    resultPath.path.push(startNode);
    
    //bool isSolutionFound = false;
    while(!nodesToVisit.empty())
    {
        CPathNode currNode = nodesToVisit.top();
        if(currNode == endNode)
        {
            //isSolutionFound = true;
            break;
        }
        nodesToVisit.pop();
        
        std::vector<CPathNode*> nbrs;
        CPathNode leftNode( currNode.row,       currNode.col - 1, 0);
        nbrs.push_back(&leftNode);
        CPathNode rightNode(currNode.row,       currNode.col + 1, 0);
        nbrs.push_back(&rightNode);
        CPathNode upNode(   currNode.row + 1,   currNode.col, 0);
        nbrs.push_back(&upNode);
        CPathNode downNode( currNode.row - 1,   currNode.col, 0);
        nbrs.push_back(&downNode);
        if(leftNode.row  >= height || leftNode.col  >= width)  leftNode.isValid  = false;
        if(rightNode.row >= height || rightNode.col >= width)  rightNode.isValid = false;
        if(upNode.row    >= height || upNode.col    >= width)  upNode.isValid    = false;
        if(downNode.row  >= height || downNode.col  >= width)  downNode.isValid  = false;
        
        for(auto it = nbrs.begin(); it != nbrs.end(); ++it)
        {
            CPathNode* currNbr = (*it);
            if(!currNbr->isValid) continue;
            
            long newCost  = costs[currNode.getFlatIndex(width)] + map->getMoveWeight(CCellCoords(currNode.col, currNode.row), object);
            long nbrIndex = currNbr->getFlatIndex(width);
            long nbrCost  = std::numeric_limits<long>::max();
            if(costs.find(nbrIndex) != costs.end()) nbrCost = costs[nbrIndex];
            if(newCost < nbrCost)
            {
                costs[nbrIndex] = newCost;
                long priority = newCost + CPathNode::heuristic(*currNbr, endNode);
                currNbr->cost = priority;
                
                nodesToVisit.push(*currNbr);
                resultPath.path.push(*currNbr);
            }
        }
        
    }
    return resultPath;
}

/*
  while (!nodes_to_visit.empty()) {
    // .top() doesn't actually remove the node
    Node cur = nodes_to_visit.top();

    if (cur == goal_node) {
      solution_found = true;
      break;
    }

    nodes_to_visit.pop();

    // check bounds and find up to four neighbors
    nbrs[0] = (cur.idx / width > 0) ? (cur.idx - width) : -1;
    nbrs[1] = (cur.idx % width > 0) ? (cur.idx - 1) : -1;
    nbrs[2] = (cur.idx / width + 1 < height) ? (cur.idx + width) : -1;
    nbrs[3] = (cur.idx % width + 1 < width) ? (cur.idx + 1) : -1;
    for (int i = 0; i < 4; ++i) {
      if (nbrs[i] >= 0) {
        // the sum of the cost so far and the cost of this move
        float new_cost = costs[cur.idx] + weights[nbrs[i]];
        if (new_cost < costs[nbrs[i]]) {
          costs[nbrs[i]] = new_cost;
          float priority = new_cost + heuristic(nbrs[i] / width,
                                                nbrs[i] % width,
                                                goal / width,
                                                goal % width);
          // paths with lower expected cost are explored first
          nodes_to_visit.push(Node(nbrs[i], priority));
          paths[nbrs[i]] = cur.idx;
        }
      }
    }
  }

  delete[] costs;
  delete[] nbrs;

  return solution_found;
}
*/