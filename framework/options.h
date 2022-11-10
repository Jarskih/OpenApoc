#include "framework/configfile.h"

namespace OpenApoc::Options
{

void dumpOptionsToLog();

extern ConfigOptionString dataPathOption;
extern ConfigOptionString cdPathOption;
extern ConfigOptionInt threadPoolSizeOption;
extern ConfigOptionString renderersOption;
extern ConfigOptionString audioBackendsOption;
extern ConfigOptionInt audioGlobalGainOption;
extern ConfigOptionInt audioSampleGainOption;
extern ConfigOptionInt audioMusicGainOption;
extern ConfigOptionInt screenWidthOption;
extern ConfigOptionInt screenHeightOption;
extern ConfigOptionBool screenFullscreenOption;
extern ConfigOptionString screenModeOption;
extern ConfigOptionInt screenDisplayNumberOption;
extern ConfigOptionInt screenScaleXOption;
extern ConfigOptionInt screenScaleYOption;
extern ConfigOptionBool screenAutoScale;
extern ConfigOptionString languageOption;

extern ConfigOptionInt frameLimit;
extern ConfigOptionInt targetFPS;
extern ConfigOptionInt swapInterval;

extern ConfigOptionBool autoScrollOption;
extern ConfigOptionBool actionMusicOption;
extern ConfigOptionBool autoExecuteOption;
extern ConfigOptionInt toolTipDelay;

extern ConfigOptionBool optionPauseOnUfoSpotted;
extern ConfigOptionBool optionPauseOnVehicleLightDamage;
extern ConfigOptionBool optionPauseOnVehicleModerateDamage;
extern ConfigOptionBool optionPauseOnVehicleHeavyDamage;
extern ConfigOptionBool optionPauseOnVehicleDestroyed;
extern ConfigOptionBool optionPauseOnVehicleEscaping;
extern ConfigOptionBool optionPauseOnVehicleNoAmmo;
extern ConfigOptionBool optionPauseOnVehicleLowFuel;
extern ConfigOptionBool optionPauseOnAgentDiedCity;
extern ConfigOptionBool optionPauseOnAgentArrived;
extern ConfigOptionBool optionPauseOnCargoArrived;
extern ConfigOptionBool optionPauseOnTransferArrived;
extern ConfigOptionBool optionPauseOnRecoveryArrived;
extern ConfigOptionBool optionPauseOnVehicleRepaired;
extern ConfigOptionBool optionPauseOnVehicleRearmed;
extern ConfigOptionBool optionPauseOnNotEnoughAmmo;
extern ConfigOptionBool optionPauseOnVehicleRefuelled;
extern ConfigOptionBool optionPauseOnNotEnoughFuel;
extern ConfigOptionBool optionPauseOnUnauthorizedVehicle;
extern ConfigOptionBool optionPauseOnHostileSpotted;
extern ConfigOptionBool optionPauseOnHostileDied;
extern ConfigOptionBool optionPauseOnUnknownDied;
extern ConfigOptionBool optionPauseOnAgentDiedBattle;
extern ConfigOptionBool optionPauseOnAgentBrainsucked;
extern ConfigOptionBool optionPauseOnAgentCriticallyWounded;
extern ConfigOptionBool optionPauseOnAgentBadlyInjured;
extern ConfigOptionBool optionPauseOnAgentInjured;
extern ConfigOptionBool optionPauseOnAgentUnderFire;
extern ConfigOptionBool optionPauseOnAgentUnconscious;
extern ConfigOptionBool optionPauseOnAgentLeftCombat;
extern ConfigOptionBool optionPauseOnAgentFrozen;
extern ConfigOptionBool optionPauseOnAgentBerserk;
extern ConfigOptionBool optionPauseOnAgentPanicked;
extern ConfigOptionBool optionPauseOnAgentPanicOver;
extern ConfigOptionBool optionPauseOnAgentPsiAttacked;
extern ConfigOptionBool optionPauseOnAgentPsiControlled;
extern ConfigOptionBool optionPauseOnAgentPsiOver;

extern ConfigOptionBool optionUFODamageModel;
extern ConfigOptionBool optionInstantExplosionDamage;
extern ConfigOptionBool optionGravliftSounds;
extern ConfigOptionBool optionNoInstantThrows;
extern ConfigOptionBool optionFerryChecksRelationshipWhenBuying;
extern ConfigOptionBool optionAllowManualCityTeleporters;
extern ConfigOptionBool optionAllowManualCargoFerry;
extern ConfigOptionBool optionAllowSoldierTaxiUse;
extern ConfigOptionBool optionAllowUnloadingClips;
extern ConfigOptionBool optionPayloadExplosion;
extern ConfigOptionBool optionDisplayUnitPaths;
extern ConfigOptionBool optionAdditionalUnitIcons;
extern ConfigOptionBool optionAllowForceFiringParallel;
extern ConfigOptionBool optionRequireLOSToMaintainPsi;
extern ConfigOptionBool optionAllowAttackingOwnedVehicles;
extern ConfigOptionBool optionCallExistingFerry;
extern ConfigOptionBool optionAlternateVehicleShieldSound;
extern ConfigOptionBool optionEnableAgentTemplates;
extern ConfigOptionBool optionStoreDroppedEquipment;
extern ConfigOptionBool optionFallingGroundVehicles;

extern ConfigOptionBool optionEnforceCargoLimits;
extern ConfigOptionBool optionAllowNearbyVehicleLootPickup;
extern ConfigOptionBool optionAllowBuildingLootDeposit;
extern ConfigOptionBool optionArmoredRoads;
extern ConfigOptionBool optionVanillaCityControls;
extern ConfigOptionBool optionCollapseRaidedBuilding;
extern ConfigOptionBool optionScrambleOnUnintentionalHit;
extern ConfigOptionBool optionMarketRight;
extern ConfigOptionBool optionDGCrashingVehicles;
extern ConfigOptionBool optionFuelCrashingVehicles;
extern ConfigOptionBool optionSkipTurbo;
extern ConfigOptionBool optionRunAndKneel;
extern ConfigOptionBool optionSeedRng;
extern ConfigOptionBool optionAutoReload;

extern ConfigOptionBool optionStunHostileAction;
extern ConfigOptionBool optionRaidHostileAction;
extern ConfigOptionBool optionBSKLauncherSound;
extern ConfigOptionBool optionInvulnerableRoads;
extern ConfigOptionBool optionATVTank;

extern ConfigOptionBool optionATVAPC;

extern ConfigOptionBool optionCrashingVehicles;
extern ConfigOptionBool optionGOAP;

extern ConfigOptionString optionScriptsList;

extern ConfigOptionBool optionInfiniteAmmoCheat;
extern ConfigOptionFloat optionDamageInflictedMultiplierCheat;
extern ConfigOptionFloat optionDamageReceivedMultiplierCheat;
extern ConfigOptionFloat optionHostilesMultiplierCheat;
extern ConfigOptionFloat optionStatGrowthMultiplierCheat;

extern ConfigOptionBool optionEnableTouchEvents;

extern ConfigOptionInt imageCacheSize;
extern ConfigOptionInt imageSetCacheSize;
extern ConfigOptionInt voxelCacheSize;
extern ConfigOptionInt fontStringCacheSize;
extern ConfigOptionInt paletteCacheSize;

extern ConfigOptionInt fileLogLevelOption;

extern ConfigOptionInt backtraceLogLevelOption;
extern ConfigOptionInt dialogLogLevelOption;

extern ConfigOptionString defaultTooltipFont;

extern ConfigOptionBool useCRCChecksum;
extern ConfigOptionBool useSHA1Checksum;

extern ConfigOptionBool enableTrace;
extern ConfigOptionString traceFile;

extern ConfigOptionString saveDirOption;
extern ConfigOptionBool packSaveOption;

extern ConfigOptionBool skipIntroOption;
extern ConfigOptionString loadGameOption;

extern ConfigOptionString modList;
extern ConfigOptionString modPath;

extern ConfigOptionBool asyncLoading;

} // namespace OpenApoc::Options
