#pragma once

#include <cuda_runtime.h>
#include <stdint.h>

#include "EngineInterface/Constants.h"
#include "EngineInterface/Enums.h"

struct ParticleTO
{
	uint64_t id;
	float energy;
	float2 pos;
	float2 vel;
    int color;

	int selected;
};

struct CellMetadataTO
{
    uint64_t nameSize;
    uint64_t nameIndex;

    uint64_t descriptionSize;
    uint64_t descriptionIndex;
};

struct ConnectionTO
{
    int cellIndex;
    float distance;
    float angleFromPrevious;
};

struct ActivityTO
{
    float channels[MAX_CHANNELS];
};

struct NeuronTO
{
    uint64_t weightsAndBiasSize;
    uint64_t weightsAndBias;
};

struct TransmitterTO
{};

struct ConstructorTO
{
    Enums::ConstructorMode mode;
    uint64_t dnaSize;
    uint64_t dna;
};

struct SensorTO
{
    Enums::SensorMode mode;
    int color;
};

struct NerveTO
{};

struct AttackerTO
{};

struct InjectorTO
{
    uint64_t dnaSize;
    uint64_t dna;
};

struct MuscleTO
{};

union CellFunctionTO
{
    NeuronTO neuron;
    TransmitterTO transmitter;
    ConstructorTO constructor;
    SensorTO sensor;
    NerveTO nerve;
    AttackerTO attacker;
    InjectorTO injector;
    MuscleTO muscle;
};

struct CellTO
{
	uint64_t id;
    ConnectionTO connections[MAX_CELL_BONDS];

    float2 pos;
    float2 vel;
	float energy;
    int color;
    int maxConnections;
	int numConnections;
	int executionOrderNumber;
    bool barrier;
    int age;

    bool underConstruction;
    bool inputBlocked;
    bool outputBlocked;

    Enums::CellFunction cellFunction;
    CellFunctionTO cellFunctionData;
    ActivityTO activity;

    CellMetadataTO metadata;

    bool activityChanged;
    int selected;
};

struct DataTO
{
	uint64_t* numCells = nullptr;
	CellTO* cells = nullptr;
    uint64_t* numParticles = nullptr;
	ParticleTO* particles = nullptr;
    uint64_t* numAuxiliaryData = nullptr;
    uint8_t* auxiliaryData = nullptr;

	bool operator==(DataTO const& other) const
	{
		return numCells == other.numCells
			&& cells == other.cells
			&& numParticles == other.numParticles
			&& particles == other.particles
            && numAuxiliaryData == other.numAuxiliaryData
            && auxiliaryData == other.auxiliaryData;
	}
};

