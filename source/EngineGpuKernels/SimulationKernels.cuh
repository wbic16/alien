#pragma once

#include <cooperative_groups.h>
#include "cuda_runtime_api.h"
#include "sm_60_atomic_functions.h"

#include "TOs.cuh"
#include "Base.cuh"
#include "Map.cuh"
#include "CellProcessor.cuh"
#include "ParticleProcessor.cuh"
#include "GarbageCollectorKernels.cuh"
#include "Operations.cuh"
#include "DebugKernels.cuh"
#include "SimulationResult.cuh" 

__global__ void cudaNextTimestep_prepare(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_physics_init(SimulationData data);
__global__ void cudaNextTimestep_physics_fillMaps(SimulationData data);
__global__ void cudaNextTimestep_physics_calcPressure(SimulationData data);
__global__ void cudaNextTimestep_physics_calcFluidForces(SimulationData data);  //requires threads/block = (ceilf(smoothingLength * 2) * 2 + 1)^2
__global__ void cudaNextTimestep_physics_calcCollisionForces(SimulationData data);
__global__ void cudaNextTimestep_physics_applyForces(SimulationData data);
__global__ void cudaNextTimestep_physics_verletPositionUpdate(SimulationData data);
__global__ void cudaNextTimestep_physics_calcConnectionForces(SimulationData data, bool considerAngles);
__global__ void cudaNextTimestep_physics_verletVelocityUpdate(SimulationData data);
__global__ void cudaNextTimestep_cellFunction_prepare_substep1(SimulationData data);
__global__ void cudaNextTimestep_cellFunction_prepare_substep2(SimulationData data);
__global__ void cudaNextTimestep_cellFunction_nerve(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_neuron(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_constructor(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_injector(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_attacker(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_defender(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_transmitter(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_muscle(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_cellFunction_sensor(SimulationData data, SimulationResult result);
__global__ void cudaNextTimestep_physics_substep7_innerFriction(SimulationData data);
__global__ void cudaNextTimestep_physics_substep8(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep1(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep2(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep3(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep4(SimulationData data);
__global__ void cudaNextTimestep_structuralOperations_substep5(SimulationData data);

__global__ void cudaInitClusterData(SimulationData data);
__global__ void cudaFindClusterIteration(SimulationData data);
__global__ void cudaFindClusterBoundaries(SimulationData data);
__global__ void cudaAccumulateClusterPosAndVel(SimulationData data);
__global__ void cudaAccumulateClusterAngularProp(SimulationData data);
__global__ void cudaApplyClusterData(SimulationData data);
