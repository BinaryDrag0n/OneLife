#ifndef OBJECT_BANK_INCLUDED
#define OBJECT_BANK_INCLUDED


#include "minorGems/game/doublePair.h"
#include "minorGems/util/SimpleVector.h"


#include "FloatRGB.h"



#include "SoundUsage.h"


void setObjectDrawAlpha( float alpha );

void setDrawColor( FloatRGB inColor );

//defined in animationBank
extern int NudeToggle;

//defined in animationBank
extern bool isTrippingEffectOn;
extern bool trippingEffectDisabled;


// tracks when creation of an object taps out nearby objects on a grid
typedef struct TapoutRecord {
        int triggerID;
        // tapout mode
        // 0: Area tapout. x radius, y radius, limit(optional).
        // 1: Coordinates. x, y.
        // 2: Directional tapout. N radius, E radius, S radius, W radius, limit(optional).
        int tapoutMode;
        int radiusN, radiusE, radiusS, radiusW; // how far to reach in +/- x and y when tapping out
        int tapoutCountLimit; // max number of objects to be tapped out by one operation
        int specificX, specificY; // specify coordinates to tap out
    } TapoutRecord;



typedef struct ObjectRecord {
        int id;
        
        char *description;

        // can it go into a container
        char containable;
        // how big of a slot is needed to contain it
        float containSize;

        // by default, when placed in a vertical container slot,
        // objects rotate 90 deg clockwise
        // this is an offset from that angle (default 0)
        double vertContainRotationOffset;
        
        
        // can it not be picked up
        char permanent;

        // true if this object should never be drawn flipped
        // (objects that have text on them, for example)
        // Note that some permanent objects are never drawn flipped 
        // automatically (those that block walking or are drawn behind player)
        char noFlip;
        
        // for objects that can only be accessed from the east and west
        // (no actions triggered from north or south)
        char sideAccess;
        

        // age you have to be to to pick something up
        int minPickupAge;
        
        // if you're > this age, you cannot pick up this object
        int maxPickupAge;
        

        // true for smaller objects that have heldOffsets relative to
        // front, moving hand
        // non-handheld objects held relative to body
        char heldInHand;

        // true for huge objects that are ridden when held (horses, cars, etc.)
        // held offset is not relative to any body part, but relative to
        // ground under body
        // note that objects cannot be BOTH heldInHand and rideable
        // (rideable overrides heldInHand)
        char rideable;
        
        // index of AnimType to be used when this object is ridden
        // default is -1
        int ridingAnimationIndex;

        
        
        // true for objects that cannot be walked through
        char blocksWalking;
        
        // true for objects that moving objects (like animals) can't pass
        // through.  All blocksWalking objects, plus some others that people
        // can walk through.
        char blocksMoving;
        

        // true if sticks out and blocks on left or right of center tile
        char wide;
        
        int leftBlockingRadius, rightBlockingRadius;

        //true for objects that when held block the player from walking 
        //on anything but the items in a choosen category.
        char blockModifier;
        

        // true for objects that are forced behind player
        // wide objects have this set to true automatically
        char drawBehindPlayer;
        
        // for individual sprite indices that are drawn behind
        // when whole object is not drawn behind
        char anySpritesBehindPlayer;
        char *spriteBehindPlayer;
        
        // toggle for additive blend mode (glow) for sprites
        char *spriteAdditiveBlend;
        

        // biome numbers where this object will naturally occur according
        // to mapChance below
        int numBiomes;
        int *biomes;
        

        // chance of occurrence naturally on map
        // value between 0 and 1 inclusive
        // Note that there's an overall chance-of-anything that is applied
        // first (controls density of map), so even if an object's value is
        // 1, it will not appear everywhere.
        // Furthermore, this value is a weight that is a fraction of the
        // total sum weight of all objects.
        float mapChance;
        
        int heatValue;
        
        // between 0 and 1, how much heat is transmitted
        float rValue;

        char person;
        // true if this person should never spawn
        // (a person for testing, a template, etc.)
        char personNoSpawn;
        
        char male;
        
        // if a person, what race number?  1, 2, 3, ....
        // 0 if not a person
        int race;

        // true if this object can be placed by server to mark a death
        char deathMarker;
        
        // true if this object can serve as a home marker
        // (remembered by client when a player makes it, and client points
        //  HOME arrow back toward it).
        char homeMarker;
        
        
        // floor objects are drawn under everything else
        // and can have other objects in the same cell
        char floor;
        
        // for vertical walls, neighboring floors auto-extended to meet
        // them
        char floorHugging;
        
        // for non floor-hugging objects that are still in wall layer
        // marked in object description with +wall
        // floorHugging objects automatically get wallLayer set to true
        char wallLayer;
        
        // true if in wall layer, but drawn in front of other walls
        char frontWall;
        

        
        int foodValue;
        int bonusValue; // This portion goes directly to the bonus part of the food bar
        
        // multiplier on walking speed when holding
        float speedMult;

        // how far to move object off center when held
        // (for right-facing hold)
        // if 0, held dead center on person center
        doublePair heldOffset;
        
        // n = not wearable
        // s = shoe
        // t = tunic
        // h = hat
        // b = bottom
        // p = backpack
        char clothing;
        
        // offset of clothing from it's default location
        // (hats is slightly above head, shoes is centered on feet,
        //  tunics is centered on body)
        doublePair clothingOffset;
        
        // how many cells away this object can kill
        // 0 for non-deadly objects
        int deadlyDistance;

        // for non-deadly uses of this object, how far away can it reach?
        // (example:  lasso an animal, but has no effect on a person)
        int useDistance;
        

        SoundUsage creationSound;
        SoundUsage usingSound;
        SoundUsage eatingSound;
        SoundUsage decaySound;

        // true if creation sound should only be triggered
        // on player-caused creation of this object (not automatic,
        // decay-caused creation).
        char creationSoundInitialOnly;
        
        // true if creation sound should always play, even if other
        // same-trigger sounds are playing
        char creationSoundForce;
        

        // if it is a container, how many slots?
        // 0 if not a container
        int numSlots;
        
        // how big of a containable can fit in each slot?
        float slotSize;
        
        doublePair *slotPos;

        // should objects be flipped vertically?
        char *slotVert;

        // index of this slot's parent in the sprite list
        // or -1 if this slot doesn't follow the motion of a sprite
        int *slotParent;
        

        // does being contained in one of this object's slots
        // adjust the passage of decay time?
        // 1.0 means normal time rate
        // > 1.0 means decay time passes faster
        // < 1.0 means longer decay times
        // must be larger than 0.0001
        float slotTimeStretch;
        
        // 0 means box-like, contained objects are y-centered by where the widest width is
        // 1 means table-like, contained objects' bottom is aligned with the slot's bottom
        // 2 means ground-like, contained objects use on-ground offsets for its contained offsets
        int slotStyle;        
        
        // true if nothing can be added/removed from container
        char slotsLocked;
        
        // true if swap is disabled for this container
        char slotsNoSwap;
        

        int numSprites;
        
        int *sprites;
        
        doublePair *spritePos;

        double *spriteRot;
        
        char *spriteHFlip;

        FloatRGB *spriteColor;
        
        // -1,-1 if sprite present whole life
        double *spriteAgeStart;
        double *spriteAgeEnd;
        
        // index in this sprite list of sprite that is motion parent of this 
        // sprite, or -1 if this sprite doesn't follow the motion of another
        int *spriteParent;

        // for person objects, is this sprite a hand?
        // (the name is left over from older implementations that made the
        //  entire arm disappear when holding something large.  This name
        //  persists in the object data files, so it's best to keep it
        //  matching in the code as well)
        char *spriteInvisibleWhenHolding;
        
        // 1 for parts of clothing that disappear when clothing put on
        // 2 for parts of clothing that disappear when clothing taken off
        // all 0 for non-clothing objects
        int *spriteInvisibleWhenWorn;
        
        char *spriteBehindSlots;
        
        char *spriteInvisibleWhenContained;
        
        char *spriteIgnoredWhenCalculatingCenterOffset;
        
        
        // flags for sprites that are special body parts
        char *spriteIsHead;
        char *spriteIsBody;
        char *spriteIsBackFoot;
        char *spriteIsFrontFoot;


        // derrived automatically for person objects from sprite name
        // tags (if they contain Eyes or Mouth)
        // only filled in if sprite bank has been loaded before object bank
        char *spriteIsEyes;
        char *spriteIsMouth;
        
        // offset of eyes from head in main segment of life
        // derrived automatically from whatever eyes are visible at age 30
        // (old eyes may have wrinkles around them, so they end up
        //  getting centered differently)
        // only filled in if sprite bank has been loaded before object bank
        doublePair mainEyesOffset;
        

        
        // number of times this object can be used before
        // something different happens
        int numUses;

        // chance that using this object will make the use count
        // decrement.  1.0 means it always decrements.
        float useChance;
        
        // flags for sprites that vanish with additional
        // use of this object
        // (example:  berries getting picked)
        char *spriteUseVanish;
        
        // sprites that appear with use
        // (example:  wear marks on an axe head)
        char *spriteUseAppear;
        

        // NULL unless we are auto-populating use dummy objects
        // then contains ( numUses - 1 ) ids for auto-generated dummy objects
        // with dummy_1 at index 0, dummy_2 at index 1, etc.
        int *useDummyIDs;
        
        // flags to manipulate which sprites of an object should be drawn
        // not saved to disk.  Defaults to all false for an object.
        char *spriteSkipDrawing;

        // dummy objects should not be left permanently in map database
        // because they can become invalid after a data update
        char isUseDummy;
        
        int useDummyParent;
        
        // which use dummy index, of parent, this is
        // indexes in parent's useDummyIDs array
        int thisUseDummyIndex;

        
        // -1 if not set
        // used to avoid recomputing height repeatedly at client/server runtime
        int cachedHeight;
        
        char apocalypseTrigger;

        char monumentStep;
        char monumentDone;
        char monumentCall;

        
        
        // NULL unless we are auto-populating variable objects
        // then contains ( N ) ids for auto-generated variable dummy objects
        // with dummy_1 at index 0, dummy_2 at index 1, etc.
        int numVariableDummyIDs;
        int *variableDummyIDs;
        
        char isVariableDummy;
        int variableDummyParent;

        // which variable dummy index, of parent, this is
        // indexes in parent's variableDummyIDs array
        int thisVariableDummyIndex;


        char isVariableHidden;


        // flags derived from various &flags in object description
        char written;
        char writable;

        char mayHaveMetadata;
        
        
        char isGlobalTriggerOn;
        char isGlobalTriggerOff;
        char isGlobalReceiver;
        // index into globalTriggers vector
        int globalTriggerIndex;
        

        char speechPipeIn;
        char speechPipeOut;
        int speechPipeIndex;

        char isFlying;
        char isFlightLanding;
        
        char isOwned;
        
        char noHighlight;
        
        // tall objects can be clicked through to reach small objects behind
        // this property disables that
        char noClickThrough;
        
        // for auto-orienting fences, walls, etc
        // all three objects know the IDs of all three objects
        int horizontalVersionID;
        int verticalVersionID;
        int cornerVersionID;
        
        
        char isTapOutTrigger;
        
        char autoDefaultTrans;

        char noBackAccess;
        
        // password-protected objects      
        // below are similar to how "writable" and "written" flags are related
        char passwordAssigner;
        char passwordProtectable;
        
        //2HOL mechanics to read written objects
        char clickToRead;
        char passToRead;
        
        SimpleVector<int> IndX;
        SimpleVector<int> IndY;
        SimpleVector<char*> IndPass;

        int alcohol;
        
        // -1 if this object is in its own yum class
        // or the object ID of its YUM parent
        // tag of +yum453 in object description specifies 453 as the yum parent 
        int yumParentID;
        
        // for floor objects that don't completely cover ground
        char noCover;
        
        // are objects in container slots invisible?
        char slotsInvis;
        
        // optional offset to default contained position for an object
        // Code estimates an ideal contained position based on widest or lowest sprite,
        // but this produces weird results in some cases.
        int containOffsetX;
        int containOffsetY;

    } ObjectRecord;


#define NUM_CLOTHING_PIECES 6


// can be applied to a person object when drawing it 
// note that these should be pointers to records managed elsewhere
// null pointers mean no clothing of that type
typedef struct ClothingSet {
        // drawn above top layer
        ObjectRecord *hat;

        // drawn behind top of back arm
        ObjectRecord *tunic;


        // drawn over front foot
        ObjectRecord *frontShoe;

        // drawn over back foot
        ObjectRecord *backShoe;

        // drawn under tunic
        ObjectRecord *bottom;
        
        // drawn on top of tunic
        ObjectRecord *backpack;
    } ClothingSet;


ClothingSet getEmptyClothingSet();

// 0 hat, 1, tunic, 2, front shoe, 3 back shoe, 4 bottom, 5 backpack
ObjectRecord *clothingByIndex( ClothingSet inSet, int inIndex );

void setClothingByIndex( ClothingSet *inSet, int inIndex, 
                         ObjectRecord *inClothing );

// gets the piece of clothing that was added to make inNewSet from inOldSet
// returns NULL if nothing added
ObjectRecord *getClothingAdded( ClothingSet *inOldSet, ClothingSet *inNewSet );



// enable index for string-based object searching
// call before init to index objects on load
// defaults to off
void enableObjectSearch( char inEnable );


// loads from objects folder
// returns number of objects that need to be loaded
//
// if inAutoGenerateUsedObjects is true, (n-1) dummy objects are generated
// for each object that has n uses.  These are not saved to disk
//
// Same for variable objects that contain the string $N in their discription
// (objects 1 - N are generated)
int initObjectBankStart( char *outRebuildingCache, 
                         char inAutoGenerateUsedObjects = false,
                         char inAutoGenerateVariableObjects = false );

// returns progress... ready for Finish when progress == 1.0
float initObjectBankStep();
void initObjectBankFinish();


void setTrippingColor( double x, double y );



// can only be called after bank init is complete
int getMaxObjectID();


void freeObjectBank();


// useful during development when new object property added
void resaveAll();


// returns ID of object
int reAddObject( ObjectRecord *inObject, 
                 char *inNewDescription = NULL,
                 char inNoWriteToFile = false, int inReplaceID = -1 );



// if inID doesn't exist, returns default object, unless inNoDefault is set
ObjectRecord *getObject( int inID, char inNoDefault = false );


// return array destroyed by caller, NULL if none found
ObjectRecord **searchObjects( const char *inSearch, 
                              int inNumToSkip, 
                              int inNumToGet, 
                              int *outNumResults, int *outNumRemaining );


int addObject( const char *inDescription,
               char inContainable,
               float inContainSize,
               double inVertContainRotationOffset,
               char inPermanent,
               char inNoFlip,
               char inSideAccess,
               int inMinPickupAge,
               int inMaxPickupAge,
               char inHeldInHand,
               char inRideable,
               int inRidingAnimationIndex,
               char inBlocksWalking,
               int inLeftBlockingRadius, int inRightBlockingRadius,
               char inBlockModifier,
               char inDrawBehindPlayer,
               char *inSpriteBehindPlayer,
               char *inSpriteAdditiveBlend,
               char *inBiomes,
               float inMapChance,
               int inHeatValue,
               float inRValue,
               char inPerson,
               char inPersonNoSpawn,
               char inMale,
               int inRace,
               char inDeathMarker,
               char inHomeMarker,
               char inTapoutTrigger,
               char *inTapoutTriggerParameters,
               char inFloor,
               char inPartialFloor,
               char inFloorHugging,
               char inWallLayer,
               char inFrontWall,
               int inFoodValue,
               int inBonusValue,
               float inSpeedMult,
               int inContainOffsetX,
               int inContainOffsetY,
               doublePair inHeldOffset,
               char inClothing,
               doublePair inClothingOffset,
               int inDeadlyDistance,
               int inUseDistance,
               SoundUsage inCreationSound,
               SoundUsage inUsingSound,
               SoundUsage inEatingSound,
               SoundUsage inDecaySound,
               char inCreationSoundInitialOnly,
               char inCreationSoundForce,
               int inNumSlots, float inSlotSize, doublePair *inSlotPos,
               int inSlotStyle,
               char *inSlotVert,
               int *inSlotParent,
               float inSlotTimeStretch,
               char inSlotsLocked,
               char inSlotsNoSwap,
               int inNumSprites, int *inSprites, 
               doublePair *inSpritePos,
               double *inSpriteRot,
               char *inSpriteHFlip,
               FloatRGB *inSpriteColor,
               double *inSpriteAgeStart,
               double *inSpriteAgeEnd,
               int *inSpriteParent,
               char *inSpriteInvisibleWhenHolding,
               int *inSpriteInvisibleWhenWorn,
               char *inSpriteBehindSlots,
               char *inSpriteInvisibleWhenContained,
               char *inSpriteIgnoredWhenCalculatingCenterOffset,
               char *inSpriteIsHead,
               char *inSpriteIsBody,
               char *inSpriteIsBackFoot,
               char *inSpriteIsFrontFoot,
               int inNumUses,
               float inUseChance,
               char *inSpriteUseVanish,
               char *inSpriteUseAppear,
               char inNoWriteToFile = false,
               int inReplaceID = -1,
               int inExistingObjectHeight = -1,
               char inConsiderIDOffset = false );




typedef struct HoldingPos {
        char valid;
        doublePair pos;
        double rot;
    } HoldingPos;


// sets max index of layers to draw on next draw call
// (can be used to draw lower layers only)
// Defaults to -1 and resets to -1 after every call (draw all layers)
void setObjectDrawLayerCutoff( int inCutoff );


// the next objects drawn will be in their contained mode
// (layers hidden when contained will be skipped)
void setDrawnObjectContained( char inContained );



// the scale of the next object drawn
// for example, object icons in minitech and vog picker should not
// scale with zoom
// remember to set the scale back to 1.0 afterwards
void setDrawnObjectScale( double inScale );




// inAge -1 for no age modifier
//
// note that inScale, which is only used by the object picker, to draw objects
// so that they fit in the picker, is not applied to clothing
//
// returns the position used to hold something 
//
// inDrawBehindSlots = 0 for back layer, 1 for front layer, 2 for both
HoldingPos drawObject( ObjectRecord *inObject, int inDrawBehindSlots,
                       doublePair inPos, 
                       double inRot, char inWorn, char inFlipH, double inAge,
                       // 1 for front arm, -1 for back arm, 0 for no hiding
                       int inHideClosestArm,
                       char inHideAllLimbs,
                       char inHeldNotInPlaceYet,
                       ClothingSet inClothing );


HoldingPos drawObject( ObjectRecord *inObject, doublePair inPos,
                       double inRot, char inWorn, char inFlipH, double inAge,
                       int inHideClosestArm,
                       char inHideAllLimbs,
                       char inHeldNotInPlaceYet,
                       ClothingSet inClothing,
                       int inNumContained, int *inContainedIDs,
                       SimpleVector<int> *inSubContained );



void deleteObjectFromBank( int inID );


char isSpriteUsed( int inSpriteID );


char isSoundUsedByObject( int inSoundID );


int getNumContainerSlots( int inID );

char isContainable( int inID );

char isApocalypseTrigger( int inID );


// 0 for nothing
// 1 for monumentStep
// 2 for monumentDone
// 3 for monumentCall
int getMonumentStatus( int inID );


// return vector NOT destroyed by caller
SimpleVector<int> *getMonumentCallObjects();




// -1 if no person object exists
int getRandomPersonObject();


// -1 if no female
int getRandomFemalePersonObject();

// get a list of all races for which we have at least one person
// these are returned in order by race number
int *getRaces( int *outNumRaces );


// number of people in race
int getRaceSize( int inRace );

// -1 if no person of this race exists
int getRandomPersonObjectOfRace( int inRace );

// gets a family member near inMotherID with max distance away in family
// spectrum 
int getRandomFamilyMember( int inRace, int inMotherID, int inFamilySpan,
                           char inForceGirl = false );



int getNextPersonObject( int inCurrentPersonObjectID );
int getPrevPersonObject( int inCurrentPersonObjectID );


// -1 if no death marker object exists
int getRandomDeathMarker();


// NOT destroyed or modified by caller
SimpleVector<int> *getAllPossibleDeathIDs();

// NOT destroyed or modified by caller
// does NOT included use dummies
SimpleVector<int> *getAllPossibleFoodIDs();

// NOT destroyed or modified by caller
SimpleVector<int> *getAllPossibleNonPermanentIDs();



// return array destroyed by caller
ObjectRecord **getAllObjects( int *outNumResults );



// returns true if sprite inPossibleAncestor is an ancestor of inChild
char checkSpriteAncestor( ObjectRecord *inRecord, int inChildIndex,
                          int inPossibleAncestorIndex );




// get the maximum diameter of an object based on 
// sprite position and dimensions
int getMaxDiameter( ObjectRecord *inObject );


// gets estimate of object height from cell center
int getObjectHeight( int inObjectID );



// picked layer can be -1 if nothing is picked
double getClosestObjectPart( ObjectRecord *inObject,
                             // can be NULL
                             ClothingSet *inClothing,
                             // can be NULL
                             SimpleVector<int> *inContained,
                             // array of vectors, one for each clothing slot
                             // can be NULL
                             SimpleVector<int> *inClothingContained,
                             // true if inObject is currently being worn
                             // controls visibility of worn/unworn layers
                             // in clothing objects
                             char inWorn,
                             double inAge,
                             int inPickedLayer,
                             char inFlip,
                             float inXCenterOffset, float inYCenterOffset,
                             int *outSprite,
                             // 0, 1, 2, 3 if clothing hit
                             int *outClothing,
                             int *outSlot,
                             // whether sprites marked as multiplicative
                             // blend-mode should be considered clickable
                             char inConsiderTransparent = true,
                             char inConsiderEmptySlots = false );


char isSpriteVisibleAtAge( ObjectRecord *inObject,
                           int inSpriteIndex,
                           double inAge );


int getBackHandIndex( ObjectRecord *inObject,
                      double inAge );

int getFrontHandIndex( ObjectRecord *inObject,
                       double inAge );


int getHeadIndex( ObjectRecord *inObject, double inAge );

int getBodyIndex( ObjectRecord *inObject, double inAge );

int getBackFootIndex( ObjectRecord *inObject, double inAge );

int getFrontFootIndex( ObjectRecord *inObject, double inAge );


void getFrontArmIndices( ObjectRecord *inObject, double inAge, 
                         SimpleVector<int> *outList );

void getBackArmIndices( ObjectRecord *inObject, double inAge, 
                        SimpleVector<int> *outList );

int getBackArmTopIndex( ObjectRecord *inObject, double inAge );


void getAllLegIndices( ObjectRecord *inObject, double inAge, 
                       SimpleVector<int> *outList );

void getAllNudeIndices( ObjectRecord *inObject, double inAge,
                       SimpleVector<int> *outList );


int getEyesIndex( ObjectRecord *inObject, double inAge );

int getMouthIndex( ObjectRecord *inObject, double inAge );



char *getBiomesString( ObjectRecord *inObject );

char *getTapoutTriggerString( ObjectRecord *inObject );


void getAllBiomes( SimpleVector<int> *inVectorToFill );


float getBiomeHeatValue( int inBiome );




// offset of object pixel center from 0,0
// note that this is computed based on the center of the widest sprite
doublePair getObjectCenterOffset( ObjectRecord *inObject );


// this is computed based on the center of the lower-most sprite
// in the object
doublePair getObjectBottomCenterOffset( ObjectRecord *inObject );


doublePair getObjectWidestSpriteCenterOffset( ObjectRecord *inObject );



// gets the largest possible radius of all wide objects
int getMaxWideRadius();


typedef struct SubsetSpriteIndexMap {
        int subIndex;
        int superIndex;
    } SubsetSpriteIndexMap;
        

// returns true if inSubObjectID's sprites are all part of inSuperObjectID
// pass in empty vector if index mapping is desired
// passed-in vector is NOT filled with anything if object is not a sprite subset
char isSpriteSubset( int inSuperObjectID, int inSubObjectID,
                     SimpleVector<SubsetSpriteIndexMap> *outMapping = NULL );



// gets arm parameters for a given held object
void getArmHoldingParameters( ObjectRecord *inHeldObject,
                              int *outHideClosestArm,
                              char *outHideAllLimbs );


void computeHeldDrawPos( HoldingPos inHoldingPos, doublePair inPos,
                         ObjectRecord *inHeldObject,
                         char inFlipH,
                         doublePair *outHeldDrawPos, double *outHeldDrawRot );



// sets vis flags in inSpriteVis based on inUsesRemaining
void setupSpriteUseVis( ObjectRecord *inObject, int inUsesRemaining,
                        char *inSpriteVis );



doublePair computeContainedCenterOffset( ObjectRecord *inContainerObject, 
                                         ObjectRecord *inContainedObject );



char bothSameUseParent( int inAObjectID, int inBObjectID );


// if this ID is a use dummy, gets the parent object ID
int getObjectParent( int inObjectID );




// processes object ID for client consumption
// hiding hidden variable object ids behind parent ID
int hideIDForClient( int inObjectID );



// leverages object's spriteSkipDrawing arrays to draw portion of
// object (drawn behind or in front) or skip actual drawing of object entirely
// saves object's spriteSkipDrawing to restore it later
void prepareToSkipSprites( ObjectRecord *inObject, 
                           char inDrawBehind, char inSkipAll = false );

// restores spriteSkipDrawing for object to what it was before
// prepareToSkipSprites was called
void restoreSkipDrawing( ObjectRecord *inObject );


int getMaxSpeechPipeIndex();



// gets number of global trigger indices
int getNumGlobalTriggers();

int getMetaTriggerObject( int inTriggerIndex );



// can a player of this age pick up a given object?
char canPickup( int inObjectID, double inPlayerAge );



TapoutRecord *getTapoutRecord( int inObjectID );



#endif