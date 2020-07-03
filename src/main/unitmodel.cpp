#include "unitmodel.h"
#include <KLocalizedContext>
#include <KLocalizedString>
#include <kunitconversion/converter.h>

UnitModel::UnitModel()
{
    units_ = KUnitConversion::Converter().category(KUnitConversion::AccelerationCategory).units();
}
QVariant UnitModel::data(const QModelIndex &index, int role) const
{
    return i18n(units_.at(index.row()).description().toLatin1());
}

int UnitModel::rowCount(const QModelIndex &parent) const
{
    return units_.count();
}
QHash<int, QByteArray> UnitModel::roleNames() const
{
    return {{Qt::DisplayRole, "name"}};
}

void UnitModel::changeUnit(QString type)
{
    emit layoutAboutToBeChanged();
    units_ = KUnitConversion::Converter().category(static_cast<KUnitConversion::CategoryId>(categoryToEnum.find(type)->second)).units();
    emit layoutChanged();
}

double UnitModel::getRet(double val, int fromType, int toType)
{
    KUnitConversion::Value fromVal(val, units_.at(fromType));
    return fromVal.convertTo(units_.at(toType)).number();
};
const std::unordered_map<QString, int> UnitModel::categoryToEnum = {{"Acceleration", KUnitConversion::AccelerationCategory},
                                                                    {"Angle", KUnitConversion::AngleCategory},
                                                                    {"Area", KUnitConversion::AreaCategory},
                                                                    {"Binary Data", KUnitConversion::BinaryDataCategory},
                                                                    {"Currency", KUnitConversion::CurrencyCategory},
                                                                    {"Density", KUnitConversion::DensityCategory},
                                                                    {"Electrical Current", KUnitConversion::ElectricalCurrentCategory},
                                                                    {"Electrical Resistance", KUnitConversion::ElectricalResistanceCategory},
                                                                    {"Energy", KUnitConversion::EnergyCategory},
                                                                    {"Force", KUnitConversion::ForceCategory},
                                                                    {"Frequency", KUnitConversion::FrequencyCategory},
                                                                    {"Fuel Efficiency", KUnitConversion::FuelEfficiencyCategory},
                                                                    {"Length", KUnitConversion::LengthCategory},
                                                                    {"Mass", KUnitConversion::MassCategory},
                                                                    {"Permeability", KUnitConversion::PermeabilityCategory},
                                                                    {"Power", KUnitConversion::PowerCategory},
                                                                    {"Pressure", KUnitConversion::PressureCategory},
                                                                    {"Temperature", KUnitConversion::TemperatureCategory},
                                                                    {"Thermal Conductivity", KUnitConversion::ThermalConductivityCategory},
                                                                    {"Thermal Flux", KUnitConversion::ThermalFluxCategory},
                                                                    {"Thermal Generation", KUnitConversion::ThermalGenerationCategory},
                                                                    {"Time", KUnitConversion::TimeCategory},
                                                                    {"Velocity", KUnitConversion::VelocityCategory},
                                                                    {"Volume", KUnitConversion::VolumeCategory},
                                                                    {"Voltage", KUnitConversion::VoltageCategory}};