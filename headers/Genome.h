#pragma once

#include <vector>
#include <unordered_map>
#include <random>
#include "config.h"

struct PairHash
{
    std::size_t operator()(const std::pair<int, int>& p) const
    {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 16);
    }
};

//struct of the Gnome 
struct ConnGene
{
	int in;
	int out;
	float weight;
	bool enabled;
	int innovation;
};

struct NodeGene
{
	enum Type { INPUT, HIDDEN, OUTPUT };
	Type type;
	int id;
};

class Genome
{
public:
    // Constructor — builds a minimal genome with the right number of inputs/outputs
    Genome(int inputs, int outputs);

    // Mutation methods — each one modifies the genome in a different way
    void mutateWeights(std::mt19937& rng);
    void mutateAddConnection(std::mt19937& rng);
    void mutateAddNode(std::mt19937& rng);

    // Crossover — combines two genomes to make a child (static because it takes two parents)
    static Genome crossover(const Genome& fitter, const Genome& weaker, std::mt19937& rng);

    // How different is this genome from another? Used for speciation
    float compatibilityDistance(const Genome& other) const;

    // The actual data — the two lists
    std::vector<NodeGene> nodes;
    std::vector<ConnGene> connections;

private:
    // Innovation number tracking — shared across ALL genomes
    static int s_nextInnovation;
    
    static std::unordered_map<std::pair<int, int>, int, PairHash> s_innovationMap;

    static int getInnovation(int in, int out);
};