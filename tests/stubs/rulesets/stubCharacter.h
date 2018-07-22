// AUTOGENERATED file, created by the tool generate_stub.py, don't edit!
// If you want to add your own functionality, instead edit the stubCharacter_custom.h file.

#ifndef STUB_RULESETS_CHARACTER_H
#define STUB_RULESETS_CHARACTER_H

#include "rulesets/Character.h"
#include "stubCharacter_custom.h"

#ifndef STUB_Character_filterExternalOperation
//#define STUB_Character_filterExternalOperation
  void Character::filterExternalOperation(const Operation &)
  {
    
  }
#endif //STUB_Character_filterExternalOperation

#ifndef STUB_Character_metabolise
//#define STUB_Character_metabolise
  void Character::metabolise(OpVector &, double ammount )
  {
    
  }
#endif //STUB_Character_metabolise

#ifndef STUB_Character_wieldDropped
//#define STUB_Character_wieldDropped
  void Character::wieldDropped()
  {
    
  }
#endif //STUB_Character_wieldDropped

#ifndef STUB_Character_findInContains
//#define STUB_Character_findInContains
  LocatedEntity* Character::findInContains(LocatedEntity * ent, const std::string & id)
  {
    return nullptr;
  }
#endif //STUB_Character_findInContains

#ifndef STUB_Character_findInInventory
//#define STUB_Character_findInInventory
  LocatedEntity* Character::findInInventory(const std::string & id)
  {
    return nullptr;
  }
#endif //STUB_Character_findInInventory

#ifndef STUB_Character_Character
//#define STUB_Character_Character
   Character::Character(const std::string & id, long intId)
    : Thing(id, intId)
    , m_proxyMind(nullptr),m_externalMind(nullptr)
  {
    
  }
#endif //STUB_Character_Character

#ifndef STUB_Character_Character_DTOR
//#define STUB_Character_Character_DTOR
   Character::~Character()
  {
    
  }
#endif //STUB_Character_Character_DTOR

#ifndef STUB_Character_linkExternal
//#define STUB_Character_linkExternal
  int Character::linkExternal(Link *)
  {
    return 0;
  }
#endif //STUB_Character_linkExternal

#ifndef STUB_Character_unlinkExternal
//#define STUB_Character_unlinkExternal
  int Character::unlinkExternal(Link *)
  {
    return 0;
  }
#endif //STUB_Character_unlinkExternal

#ifndef STUB_Character_startTask
//#define STUB_Character_startTask
  int Character::startTask(Task *, const Operation & op, OpVector &)
  {
    return 0;
  }
#endif //STUB_Character_startTask

#ifndef STUB_Character_updateTask
//#define STUB_Character_updateTask
  void Character::updateTask(OpVector &)
  {
    
  }
#endif //STUB_Character_updateTask

#ifndef STUB_Character_clearTask
//#define STUB_Character_clearTask
  void Character::clearTask(OpVector &)
  {
    
  }
#endif //STUB_Character_clearTask

#ifndef STUB_Character_getThoughts
//#define STUB_Character_getThoughts
  std::vector<Atlas::Objects::Root> Character::getThoughts() const
  {
    return std::vector<Atlas::Objects::Root>();
  }
#endif //STUB_Character_getThoughts

#ifndef STUB_Character_operation
//#define STUB_Character_operation
  void Character::operation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_operation

#ifndef STUB_Character_externalOperation
//#define STUB_Character_externalOperation
  void Character::externalOperation(const Operation & op, Link &)
  {
    
  }
#endif //STUB_Character_externalOperation

#ifndef STUB_Character_ImaginaryOperation
//#define STUB_Character_ImaginaryOperation
  void Character::ImaginaryOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_ImaginaryOperation

#ifndef STUB_Character_InfoOperation
//#define STUB_Character_InfoOperation
  void Character::InfoOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_InfoOperation

#ifndef STUB_Character_TickOperation
//#define STUB_Character_TickOperation
  void Character::TickOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_TickOperation

#ifndef STUB_Character_TalkOperation
//#define STUB_Character_TalkOperation
  void Character::TalkOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_TalkOperation

#ifndef STUB_Character_NourishOperation
//#define STUB_Character_NourishOperation
  void Character::NourishOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_NourishOperation

#ifndef STUB_Character_UseOperation
//#define STUB_Character_UseOperation
  void Character::UseOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_UseOperation

#ifndef STUB_Character_WieldOperation
//#define STUB_Character_WieldOperation
  void Character::WieldOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_WieldOperation

#ifndef STUB_Character_ActuateOperation
//#define STUB_Character_ActuateOperation
  void Character::ActuateOperation(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_ActuateOperation

#ifndef STUB_Character_RelayOperation
//#define STUB_Character_RelayOperation
  void Character::RelayOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_RelayOperation

#ifndef STUB_Character_mindActuateOperation
//#define STUB_Character_mindActuateOperation
  void Character::mindActuateOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindActuateOperation

#ifndef STUB_Character_mindCombineOperation
//#define STUB_Character_mindCombineOperation
  void Character::mindCombineOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindCombineOperation

#ifndef STUB_Character_mindCreateOperation
//#define STUB_Character_mindCreateOperation
  void Character::mindCreateOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindCreateOperation

#ifndef STUB_Character_mindDeleteOperation
//#define STUB_Character_mindDeleteOperation
  void Character::mindDeleteOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindDeleteOperation

#ifndef STUB_Character_mindDivideOperation
//#define STUB_Character_mindDivideOperation
  void Character::mindDivideOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindDivideOperation

#ifndef STUB_Character_mindEatOperation
//#define STUB_Character_mindEatOperation
  void Character::mindEatOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindEatOperation

#ifndef STUB_Character_mindGoalInfoOperation
//#define STUB_Character_mindGoalInfoOperation
  void Character::mindGoalInfoOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindGoalInfoOperation

#ifndef STUB_Character_mindImaginaryOperation
//#define STUB_Character_mindImaginaryOperation
  void Character::mindImaginaryOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindImaginaryOperation

#ifndef STUB_Character_mindLookOperation
//#define STUB_Character_mindLookOperation
  void Character::mindLookOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindLookOperation

#ifndef STUB_Character_mindMoveOperation
//#define STUB_Character_mindMoveOperation
  void Character::mindMoveOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindMoveOperation

#ifndef STUB_Character_mindSetOperation
//#define STUB_Character_mindSetOperation
  void Character::mindSetOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindSetOperation

#ifndef STUB_Character_mindSetupOperation
//#define STUB_Character_mindSetupOperation
  void Character::mindSetupOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindSetupOperation

#ifndef STUB_Character_mindTalkOperation
//#define STUB_Character_mindTalkOperation
  void Character::mindTalkOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindTalkOperation

#ifndef STUB_Character_mindThoughtOperation
//#define STUB_Character_mindThoughtOperation
  void Character::mindThoughtOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindThoughtOperation

#ifndef STUB_Character_mindThinkOperation
//#define STUB_Character_mindThinkOperation
  void Character::mindThinkOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindThinkOperation

#ifndef STUB_Character_mindTickOperation
//#define STUB_Character_mindTickOperation
  void Character::mindTickOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindTickOperation

#ifndef STUB_Character_mindTouchOperation
//#define STUB_Character_mindTouchOperation
  void Character::mindTouchOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindTouchOperation

#ifndef STUB_Character_mindUpdateOperation
//#define STUB_Character_mindUpdateOperation
  void Character::mindUpdateOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindUpdateOperation

#ifndef STUB_Character_mindUseOperation
//#define STUB_Character_mindUseOperation
  void Character::mindUseOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindUseOperation

#ifndef STUB_Character_mindWieldOperation
//#define STUB_Character_mindWieldOperation
  void Character::mindWieldOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindWieldOperation

#ifndef STUB_Character_mindOtherOperation
//#define STUB_Character_mindOtherOperation
  void Character::mindOtherOperation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_Character_mindOtherOperation

#ifndef STUB_Character_w2mSightOperation
//#define STUB_Character_w2mSightOperation
  bool Character::w2mSightOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mSightOperation

#ifndef STUB_Character_w2mSoundOperation
//#define STUB_Character_w2mSoundOperation
  bool Character::w2mSoundOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mSoundOperation

#ifndef STUB_Character_w2mTouchOperation
//#define STUB_Character_w2mTouchOperation
  bool Character::w2mTouchOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mTouchOperation

#ifndef STUB_Character_w2mTickOperation
//#define STUB_Character_w2mTickOperation
  bool Character::w2mTickOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mTickOperation

#ifndef STUB_Character_w2mUnseenOperation
//#define STUB_Character_w2mUnseenOperation
  bool Character::w2mUnseenOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mUnseenOperation

#ifndef STUB_Character_w2mSetupOperation
//#define STUB_Character_w2mSetupOperation
  bool Character::w2mSetupOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mSetupOperation

#ifndef STUB_Character_w2mAppearanceOperation
//#define STUB_Character_w2mAppearanceOperation
  bool Character::w2mAppearanceOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mAppearanceOperation

#ifndef STUB_Character_w2mDisappearanceOperation
//#define STUB_Character_w2mDisappearanceOperation
  bool Character::w2mDisappearanceOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mDisappearanceOperation

#ifndef STUB_Character_w2mErrorOperation
//#define STUB_Character_w2mErrorOperation
  bool Character::w2mErrorOperation(const Operation &)
  {
    return false;
  }
#endif //STUB_Character_w2mErrorOperation

#ifndef STUB_Character_w2mThoughtOperation
//#define STUB_Character_w2mThoughtOperation
  bool Character::w2mThoughtOperation(const Operation & op)
  {
    return false;
  }
#endif //STUB_Character_w2mThoughtOperation

#ifndef STUB_Character_w2mThinkOperation
//#define STUB_Character_w2mThinkOperation
  bool Character::w2mThinkOperation(const Operation & op)
  {
    return false;
  }
#endif //STUB_Character_w2mThinkOperation

#ifndef STUB_Character_w2mCommuneOperation
//#define STUB_Character_w2mCommuneOperation
  bool Character::w2mCommuneOperation(const Operation & op)
  {
    return false;
  }
#endif //STUB_Character_w2mCommuneOperation

#ifndef STUB_Character_w2mRelayOperation
//#define STUB_Character_w2mRelayOperation
  bool Character::w2mRelayOperation(const Operation & op)
  {
    return false;
  }
#endif //STUB_Character_w2mRelayOperation

#ifndef STUB_Character_sendMind
//#define STUB_Character_sendMind
  void Character::sendMind(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_sendMind

#ifndef STUB_Character_mind2body
//#define STUB_Character_mind2body
  void Character::mind2body(const Operation & op, OpVector &)
  {
    
  }
#endif //STUB_Character_mind2body

#ifndef STUB_Character_world2mind
//#define STUB_Character_world2mind
  bool Character::world2mind(const Operation & op)
  {
    return false;
  }
#endif //STUB_Character_world2mind


#endif