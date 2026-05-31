#include "Genome.h"
#include <algorithm>
#include <cmath>

//define static variables outside of the class
int Genome::s_nextInnovation = 0;
std::unordered_map<std::pair<int, int>, int, PairHash> Genome::s_innovationMap;

//Constructor — builds a minimal genome with the right number of inputs/outputs
Genome::Genome(int inputs, int outputs)
{
    for( int i = 0; i < inputs; i++ )
    {
		//set the variables of the node and push it to the vector of nodes
        NodeGene node;
        node.id = i;
        node.type = NodeGene::INPUT;
        nodes.push_back(node);
        
	}
    //Outtput
    NodeGene output;
    output.id = inputs;
    output.type = NodeGene::OUTPUT;
    nodes.push_back(output);

}

int Genome::getInnovation(int in, int out)
{
    //check if the pair is out or in ? 

	auto it = s_innovationMap.find({ in, out });
    if(it != s_innovationMap.end()) {
        return it->second;
    }
    else {
        int innovation = s_nextInnovation++;
        s_innovationMap[{ in, out }] = innovation;
        return innovation;
	}
}

void Genome::mutateWeights(std::mt19937& rng)
{
    std::uniform_real_distribution<float> prob(0.0f, 1.0f);
    std::normal_distribution<float> perturb(0.0f, 0.3f);
    // loop through connections
    for (auto& conn : connections)
    {
        if(prob(rng) > Config::MUTATE_WEIGHT_RATE)
            {
            continue; // skip mutation
		}
        if(prob(rng) < Config::MUTATE_WEIGHT_PERTURB)
        {
            // perturb weight
            conn.weight += perturb(rng);
        }
        else
        {
            // assign new weight
            conn.weight = std::uniform_real_distribution<float>(-2.0f, 2.0f)(rng);
        }
    }
}

void Genome::mutateAddConnection(std::mt19937& rng)
{
    //random index to pick nodes.
    std::uniform_int_distribution<int> nodeDist(0, (int)nodes.size() - 1);
}
