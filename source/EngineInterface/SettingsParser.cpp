#include "SettingsParser.h"

#include "GeneralSettings.h"
#include "Settings.h"

boost::property_tree::ptree SettingsParser::encode(uint64_t timestep, Settings settings)
{
    boost::property_tree::ptree tree;
    encodeDecode(tree, timestep, settings, ParserTask::Encode);
    return tree;
}

std::pair<uint64_t, Settings> SettingsParser::decodeTimestepAndSettings(boost::property_tree::ptree tree)
{
    uint64_t timestep;
    Settings settings;
    encodeDecode(tree, timestep, settings, ParserTask::Decode);
    return std::make_pair(timestep, settings);
}

namespace
{
    std::unordered_map<SpotShape, std::string> shapeStringMap = {{SpotShape::Circular, "circular"}, {SpotShape::Rectangular, "rectangular"}};
    std::unordered_map<std::string, SpotShape> shapeEnumMap = {{"circular", SpotShape::Circular}, {"rectangular", SpotShape::Rectangular}};
}

void SettingsParser::encodeDecode(boost::property_tree::ptree& tree, uint64_t& timestep, Settings& settings, ParserTask parserTask)
{
    Settings defaultSettings;

    //general settings
    JsonParser::encodeDecode(tree, timestep, uint64_t(0), "general.time step", parserTask);
    JsonParser::encodeDecode(tree, settings.generalSettings.worldSizeX, defaultSettings.generalSettings.worldSizeX, "general.world size.x", parserTask);
    JsonParser::encodeDecode(tree, settings.generalSettings.worldSizeY, defaultSettings.generalSettings.worldSizeY, "general.world size.y", parserTask);

    //simulation parameters
    auto& simPar = settings.simulationParameters;
    auto& defaultPar = defaultSettings.simulationParameters;
    JsonParser::encodeDecode(tree, simPar.timestepSize, defaultPar.timestepSize, "simulation parameters.time step size", parserTask);
    JsonParser::encodeDecode(tree, simPar.spotValues.friction, defaultPar.spotValues.friction, "simulation parameters.friction", parserTask);
    JsonParser::encodeDecode(tree, simPar.spotValues.rigidity, defaultPar.spotValues.rigidity, "simulation parameters.rigidity", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.spotValues.cellBindingForce, defaultPar.spotValues.cellBindingForce, "simulation parameters.cell.binding force", parserTask);
    JsonParser::encodeDecode(tree, simPar.cellMaxVel, defaultPar.cellMaxVel, "simulation parameters.cell.max velocity", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.cellMaxBindingDistance, defaultPar.cellMaxBindingDistance, "simulation parameters.cell.max binding distance", parserTask);
    JsonParser::encodeDecode(tree, simPar.cellRepulsionStrength, defaultPar.cellRepulsionStrength, "simulation parameters.cell.repulsion strength", parserTask);

    JsonParser::encodeDecode(tree, simPar.cellMinDistance, defaultPar.cellMinDistance, "simulation parameters.cell.min distance", parserTask);
    JsonParser::encodeDecode(tree, simPar.cellMaxCollisionDistance, defaultPar.cellMaxCollisionDistance, "simulation parameters.cell.max distance", parserTask);
    JsonParser::encodeDecode(tree, simPar.spotValues.cellMaxForce, defaultPar.spotValues.cellMaxForce, "simulation parameters.cell.max force", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.cellMaxForceDecayProb, defaultPar.cellMaxForceDecayProb, "simulation parameters.cell.max force decay probability", parserTask);
    JsonParser::encodeDecode(tree, simPar.cellMaxBonds, defaultPar.cellMaxBonds, "simulation parameters.cell.max bonds", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.cellMaxExecutionOrderNumber, defaultPar.cellMaxExecutionOrderNumber, "simulation parameters.cell.max execution order number", parserTask);
    JsonParser::encodeDecode(tree, simPar.spotValues.cellMinEnergy, defaultPar.spotValues.cellMinEnergy, "simulation parameters.cell.min energy", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.spotValues.cellFusionVelocity, defaultPar.spotValues.cellFusionVelocity, "simulation parameters.cell.fusion velocity", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.spotValues.cellMaxBindingEnergy, simPar.spotValues.cellMaxBindingEnergy, "simulation parameters.cell.max binding energy", parserTask);
    for (int i = 0; i < 7; ++i) {
        JsonParser::encodeDecode(
            tree,
            simPar.spotValues.cellColorTransitionDuration[i],
            defaultPar.spotValues.cellColorTransitionDuration[i],
            "simulation parameters.cell.color transition rules.duration[" + std::to_string(i) + "]",
            parserTask);
        JsonParser::encodeDecode(
            tree,
            simPar.spotValues.cellColorTransitionTargetColor[i],
            defaultPar.spotValues.cellColorTransitionTargetColor[i],
            "simulation parameters.cell.color transition rules.target color[" + std::to_string(i) + "]",
            parserTask);
    }
    JsonParser::encodeDecode(
        tree, simPar.cellFunctionWeaponStrength, defaultPar.cellFunctionWeaponStrength, "simulation parameters.cell.function.weapon.strength", parserTask);
    JsonParser::encodeDecode(
        tree,
        simPar.spotValues.cellFunctionWeaponEnergyCost,
        defaultPar.spotValues.cellFunctionWeaponEnergyCost,
        "simulation parameters.cell.function.weapon.energy cost",
        parserTask);
    JsonParser::encodeDecode(
        tree,
        simPar.spotValues.cellFunctionWeaponGeometryDeviationExponent,
        defaultPar.spotValues.cellFunctionWeaponGeometryDeviationExponent,
        "simulation parameters.cell.function.weapon.geometry deviation exponent",
        parserTask);
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            JsonParser::encodeDecode(
                tree,
                simPar.spotValues.cellFunctionWeaponFoodChainColorMatrix[i][j],
                defaultPar.spotValues.cellFunctionWeaponFoodChainColorMatrix[i][j],
                "simulation parameters.cell.function.weapon.food chain color matrix[" + std::to_string(i) + ", " + std::to_string(j) + "]",
                parserTask);
        }
    }
    JsonParser::encodeDecode(
        tree,
        simPar.spotValues.cellFunctionWeaponConnectionsMismatchPenalty,
        defaultPar.spotValues.cellFunctionWeaponConnectionsMismatchPenalty,
        "simulation parameters.cell.function.weapon.connections mismatch penalty",
        parserTask);
    JsonParser::encodeDecode(
        tree, simPar.cellFunctionSensorRange, defaultPar.cellFunctionSensorRange, "simulation parameters.cell.function.sensor.range", parserTask);
    JsonParser::encodeDecode(tree, simPar.radiationExponent, defaultPar.radiationExponent, "simulation parameters.radiation.exponent", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.spotValues.radiationFactor, defaultPar.spotValues.radiationFactor, "simulation parameters.radiation.factor", parserTask);
    JsonParser::encodeDecode(tree, simPar.radiationProb, defaultPar.radiationProb, "simulation parameters.radiation.probability", parserTask);
    JsonParser::encodeDecode(
        tree, simPar.radiationVelocityMultiplier, defaultPar.radiationVelocityMultiplier, "simulation parameters.radiation.velocity multiplier", parserTask);
    JsonParser::encodeDecode(
        tree,
        simPar.radiationVelocityPerturbation,
        defaultPar.radiationVelocityPerturbation,
        "simulation parameters.radiation.velocity perturbation",
        parserTask);

    //spots
    auto& spots = settings.simulationParametersSpots;
    auto& defaultSpots = defaultSettings.simulationParametersSpots;
    JsonParser::encodeDecode(tree, spots.numSpots, defaultSpots.numSpots, "simulation parameters.spots.num spots", parserTask);
    for (int index = 0; index <= 1; ++index) {
        std::string base = "simulation parameters.spots." + std::to_string(index) + ".";
        auto& spot = spots.spots[index];
        auto& defaultSpot = defaultSpots.spots[index];
        JsonParser::encodeDecode(tree, spot.color, defaultSpot.color, base + "color", parserTask);
        JsonParser::encodeDecode(tree, spot.posX, defaultSpot.posX, base + "pos.x", parserTask);
        JsonParser::encodeDecode(tree, spot.posY, defaultSpot.posY, base + "pos.y", parserTask);

        auto shapeString = shapeStringMap.at(spot.shape);
        JsonParser::encodeDecode(tree, shapeString, shapeStringMap.at(defaultSpot.shape), base + "shape", parserTask);
        spot.shape = shapeEnumMap.at(shapeString);

        JsonParser::encodeDecode(tree, spot.width, defaultSpot.width, base + "core width", parserTask);
        JsonParser::encodeDecode(tree, spot.height, defaultSpot.height, base + "core height", parserTask);
        JsonParser::encodeDecode(tree, spot.coreRadius, defaultSpot.coreRadius, base + "core radius", parserTask);
        JsonParser::encodeDecode(tree, spot.fadeoutRadius, defaultSpot.fadeoutRadius, base + "fadeout radius", parserTask);
        JsonParser::encodeDecode(tree, spot.values.friction, defaultSpot.values.friction, base + "friction", parserTask);
        JsonParser::encodeDecode(tree, spot.values.rigidity, defaultSpot.values.rigidity, base + "rigidity", parserTask);
        JsonParser::encodeDecode(tree, spot.values.radiationFactor, defaultSpot.values.radiationFactor, base + "radiation.factor", parserTask);
        JsonParser::encodeDecode(tree, spot.values.cellMaxForce, defaultSpot.values.cellMaxForce, base + "cell.max force", parserTask);
        JsonParser::encodeDecode(tree, spot.values.cellMinEnergy, defaultSpot.values.cellMinEnergy, base + "cell.min energy", parserTask);

        JsonParser::encodeDecode(tree, spot.values.cellBindingForce, defaultSpot.values.cellBindingForce, base + "cell.binding force", parserTask);
        JsonParser::encodeDecode(tree, spot.values.cellFusionVelocity, defaultSpot.values.cellFusionVelocity, base + "cell.fusion velocity", parserTask);
        JsonParser::encodeDecode(tree, spot.values.cellMaxBindingEnergy, defaultSpot.values.cellMaxBindingEnergy, base + "cell.max binding energy", parserTask);

        for (int i = 0; i < 7; ++i) {
            JsonParser::encodeDecode(
                tree,
                spot.values.cellColorTransitionDuration[i],
                defaultSpot.values.cellColorTransitionDuration[i],
                base + "cell.color transition rules.duration[" + std::to_string(i) + "]",
                parserTask);
            JsonParser::encodeDecode(
                tree,
                spot.values.cellColorTransitionTargetColor[i],
                defaultSpot.values.cellColorTransitionTargetColor[i],
                base + "cell.color transition rules.target color[" + std::to_string(i) + "]",
                parserTask);
        }

        JsonParser::encodeDecode(
            tree,
            spot.values.cellFunctionWeaponEnergyCost,
            defaultSpot.values.cellFunctionWeaponEnergyCost,
            base + "cell.function.weapon.energy cost",
            parserTask);
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                JsonParser::encodeDecode(
                    tree,
                    spot.values.cellFunctionWeaponFoodChainColorMatrix[i][j],
                    defaultSpot.values.cellFunctionWeaponFoodChainColorMatrix[i][j],
                    base + "function.weapon.color matrix[" + std::to_string(i) + ", " + std::to_string(j) + "]",
                    parserTask);
            }
        }
        JsonParser::encodeDecode(
            tree,
            spot.values.cellFunctionWeaponGeometryDeviationExponent,
            defaultSpot.values.cellFunctionWeaponGeometryDeviationExponent,
            base + "cell.function.weapon.geometry deviation exponent",
            parserTask);
        JsonParser::encodeDecode(
            tree,
            spot.values.cellFunctionWeaponConnectionsMismatchPenalty,
            defaultSpot.values.cellFunctionWeaponConnectionsMismatchPenalty,
            base + "cell.function.weapon.connections mismatch penalty",
            parserTask);
    }

    //flow field settings
    JsonParser::encodeDecode(tree, settings.flowFieldSettings.active, defaultSettings.flowFieldSettings.active, "flow field.active", parserTask);
    JsonParser::encodeDecode(tree, settings.flowFieldSettings.numCenters, defaultSettings.flowFieldSettings.numCenters, "flow field.num centers", parserTask);
    for (int i = 0; i < 2; ++i) {
        std::string node = "flow field.center" + std::to_string(i) + ".";
        auto& radialData = settings.flowFieldSettings.centers[i];
        auto& defaultRadialData = defaultSettings.flowFieldSettings.centers[i];
        JsonParser::encodeDecode(tree, radialData.posX, defaultRadialData.posX, node + "pos.x", parserTask);
        JsonParser::encodeDecode(tree, radialData.posY, defaultRadialData.posY, node + "pos.y", parserTask);
        JsonParser::encodeDecode(tree, radialData.radius, defaultRadialData.radius, node + "radius", parserTask);
        JsonParser::encodeDecode(tree, radialData.strength, defaultRadialData.strength, node + "strength", parserTask);
    }
}
