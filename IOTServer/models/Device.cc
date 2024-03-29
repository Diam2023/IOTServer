/**
 *
 *  Device.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Device.h"
#include "SubscribeMap.h"
#include "Topic.h"
#include "UserDeviceActionMap.h"
#include "UserDeviceAliasMap.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::iot_server;

const std::string Device::Cols::_device_id = "device_id";
const std::string Device::Cols::_device_sn = "device_sn";
const std::string Device::Cols::_device_name = "device_name";
const std::string Device::Cols::_device_comment = "device_comment";
const std::string Device::Cols::_target_permission_level = "target_permission_level";
const std::string Device::primaryKeyName = "device_id";
const bool Device::hasPrimaryKey = true;
const std::string Device::tableName = "device";

const std::vector<typename Device::MetaData> Device::metaData_={
{"device_id","uint32_t","int unsigned",4,1,1,1},
{"device_sn","std::string","varchar(100)",100,0,0,1},
{"device_name","std::string","varchar(100)",100,0,0,1},
{"device_comment","std::string","varchar(1024)",1024,0,0,0},
{"target_permission_level","uint32_t","int unsigned",4,0,0,1}
};
const std::string &Device::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Device::Device(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["device_id"].isNull())
        {
            deviceId_=std::make_shared<uint32_t>(r["device_id"].as<uint32_t>());
        }
        if(!r["device_sn"].isNull())
        {
            deviceSn_=std::make_shared<std::string>(r["device_sn"].as<std::string>());
        }
        if(!r["device_name"].isNull())
        {
            deviceName_=std::make_shared<std::string>(r["device_name"].as<std::string>());
        }
        if(!r["device_comment"].isNull())
        {
            deviceComment_=std::make_shared<std::string>(r["device_comment"].as<std::string>());
        }
        if(!r["target_permission_level"].isNull())
        {
            targetPermissionLevel_=std::make_shared<uint32_t>(r["target_permission_level"].as<uint32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 5 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            deviceId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            deviceSn_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            deviceName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            deviceComment_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            targetPermissionLevel_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
    }

}

Device::Device(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            deviceId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            deviceSn_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            deviceName_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            deviceComment_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            targetPermissionLevel_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
}

Device::Device(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("device_id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["device_id"].isNull())
        {
            deviceId_=std::make_shared<uint32_t>((uint32_t)pJson["device_id"].asUInt64());
        }
    }
    if(pJson.isMember("device_sn"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["device_sn"].isNull())
        {
            deviceSn_=std::make_shared<std::string>(pJson["device_sn"].asString());
        }
    }
    if(pJson.isMember("device_name"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["device_name"].isNull())
        {
            deviceName_=std::make_shared<std::string>(pJson["device_name"].asString());
        }
    }
    if(pJson.isMember("device_comment"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["device_comment"].isNull())
        {
            deviceComment_=std::make_shared<std::string>(pJson["device_comment"].asString());
        }
    }
    if(pJson.isMember("target_permission_level"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["target_permission_level"].isNull())
        {
            targetPermissionLevel_=std::make_shared<uint32_t>((uint32_t)pJson["target_permission_level"].asUInt64());
        }
    }
}

void Device::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            deviceId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            deviceSn_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            deviceName_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            deviceComment_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            targetPermissionLevel_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
}

void Device::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("device_id"))
    {
        if(!pJson["device_id"].isNull())
        {
            deviceId_=std::make_shared<uint32_t>((uint32_t)pJson["device_id"].asUInt64());
        }
    }
    if(pJson.isMember("device_sn"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["device_sn"].isNull())
        {
            deviceSn_=std::make_shared<std::string>(pJson["device_sn"].asString());
        }
    }
    if(pJson.isMember("device_name"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["device_name"].isNull())
        {
            deviceName_=std::make_shared<std::string>(pJson["device_name"].asString());
        }
    }
    if(pJson.isMember("device_comment"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["device_comment"].isNull())
        {
            deviceComment_=std::make_shared<std::string>(pJson["device_comment"].asString());
        }
    }
    if(pJson.isMember("target_permission_level"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["target_permission_level"].isNull())
        {
            targetPermissionLevel_=std::make_shared<uint32_t>((uint32_t)pJson["target_permission_level"].asUInt64());
        }
    }
}

const uint32_t &Device::getValueOfDeviceId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(deviceId_)
        return *deviceId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Device::getDeviceId() const noexcept
{
    return deviceId_;
}
void Device::setDeviceId(const uint32_t &pDeviceId) noexcept
{
    deviceId_ = std::make_shared<uint32_t>(pDeviceId);
    dirtyFlag_[0] = true;
}
const typename Device::PrimaryKeyType & Device::getPrimaryKey() const
{
    assert(deviceId_);
    return *deviceId_;
}

const std::string &Device::getValueOfDeviceSn() const noexcept
{
    const static std::string defaultValue = std::string();
    if(deviceSn_)
        return *deviceSn_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Device::getDeviceSn() const noexcept
{
    return deviceSn_;
}
void Device::setDeviceSn(const std::string &pDeviceSn) noexcept
{
    deviceSn_ = std::make_shared<std::string>(pDeviceSn);
    dirtyFlag_[1] = true;
}
void Device::setDeviceSn(std::string &&pDeviceSn) noexcept
{
    deviceSn_ = std::make_shared<std::string>(std::move(pDeviceSn));
    dirtyFlag_[1] = true;
}

const std::string &Device::getValueOfDeviceName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(deviceName_)
        return *deviceName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Device::getDeviceName() const noexcept
{
    return deviceName_;
}
void Device::setDeviceName(const std::string &pDeviceName) noexcept
{
    deviceName_ = std::make_shared<std::string>(pDeviceName);
    dirtyFlag_[2] = true;
}
void Device::setDeviceName(std::string &&pDeviceName) noexcept
{
    deviceName_ = std::make_shared<std::string>(std::move(pDeviceName));
    dirtyFlag_[2] = true;
}

const std::string &Device::getValueOfDeviceComment() const noexcept
{
    const static std::string defaultValue = std::string();
    if(deviceComment_)
        return *deviceComment_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Device::getDeviceComment() const noexcept
{
    return deviceComment_;
}
void Device::setDeviceComment(const std::string &pDeviceComment) noexcept
{
    deviceComment_ = std::make_shared<std::string>(pDeviceComment);
    dirtyFlag_[3] = true;
}
void Device::setDeviceComment(std::string &&pDeviceComment) noexcept
{
    deviceComment_ = std::make_shared<std::string>(std::move(pDeviceComment));
    dirtyFlag_[3] = true;
}
void Device::setDeviceCommentToNull() noexcept
{
    deviceComment_.reset();
    dirtyFlag_[3] = true;
}

const uint32_t &Device::getValueOfTargetPermissionLevel() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(targetPermissionLevel_)
        return *targetPermissionLevel_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Device::getTargetPermissionLevel() const noexcept
{
    return targetPermissionLevel_;
}
void Device::setTargetPermissionLevel(const uint32_t &pTargetPermissionLevel) noexcept
{
    targetPermissionLevel_ = std::make_shared<uint32_t>(pTargetPermissionLevel);
    dirtyFlag_[4] = true;
}

void Device::updateId(const uint64_t id)
{
    deviceId_ = std::make_shared<uint32_t>(static_cast<uint32_t>(id));
}

const std::vector<std::string> &Device::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "device_sn",
        "device_name",
        "device_comment",
        "target_permission_level"
    };
    return inCols;
}

void Device::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getDeviceSn())
        {
            binder << getValueOfDeviceSn();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDeviceName())
        {
            binder << getValueOfDeviceName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDeviceComment())
        {
            binder << getValueOfDeviceComment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTargetPermissionLevel())
        {
            binder << getValueOfTargetPermissionLevel();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Device::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    return ret;
}

void Device::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getDeviceSn())
        {
            binder << getValueOfDeviceSn();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getDeviceName())
        {
            binder << getValueOfDeviceName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDeviceComment())
        {
            binder << getValueOfDeviceComment();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTargetPermissionLevel())
        {
            binder << getValueOfTargetPermissionLevel();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Device::toJson() const
{
    Json::Value ret;
    if(getDeviceId())
    {
        ret["device_id"]=getValueOfDeviceId();
    }
    else
    {
        ret["device_id"]=Json::Value();
    }
    if(getDeviceSn())
    {
        ret["device_sn"]=getValueOfDeviceSn();
    }
    else
    {
        ret["device_sn"]=Json::Value();
    }
    if(getDeviceName())
    {
        ret["device_name"]=getValueOfDeviceName();
    }
    else
    {
        ret["device_name"]=Json::Value();
    }
    if(getDeviceComment())
    {
        ret["device_comment"]=getValueOfDeviceComment();
    }
    else
    {
        ret["device_comment"]=Json::Value();
    }
    if(getTargetPermissionLevel())
    {
        ret["target_permission_level"]=getValueOfTargetPermissionLevel();
    }
    else
    {
        ret["target_permission_level"]=Json::Value();
    }
    return ret;
}

Json::Value Device::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 5)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getDeviceId())
            {
                ret[pMasqueradingVector[0]]=getValueOfDeviceId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getDeviceSn())
            {
                ret[pMasqueradingVector[1]]=getValueOfDeviceSn();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getDeviceName())
            {
                ret[pMasqueradingVector[2]]=getValueOfDeviceName();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getDeviceComment())
            {
                ret[pMasqueradingVector[3]]=getValueOfDeviceComment();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getTargetPermissionLevel())
            {
                ret[pMasqueradingVector[4]]=getValueOfTargetPermissionLevel();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getDeviceId())
    {
        ret["device_id"]=getValueOfDeviceId();
    }
    else
    {
        ret["device_id"]=Json::Value();
    }
    if(getDeviceSn())
    {
        ret["device_sn"]=getValueOfDeviceSn();
    }
    else
    {
        ret["device_sn"]=Json::Value();
    }
    if(getDeviceName())
    {
        ret["device_name"]=getValueOfDeviceName();
    }
    else
    {
        ret["device_name"]=Json::Value();
    }
    if(getDeviceComment())
    {
        ret["device_comment"]=getValueOfDeviceComment();
    }
    else
    {
        ret["device_comment"]=Json::Value();
    }
    if(getTargetPermissionLevel())
    {
        ret["target_permission_level"]=getValueOfTargetPermissionLevel();
    }
    else
    {
        ret["target_permission_level"]=Json::Value();
    }
    return ret;
}

bool Device::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("device_id"))
    {
        if(!validJsonOfField(0, "device_id", pJson["device_id"], err, true))
            return false;
    }
    if(pJson.isMember("device_sn"))
    {
        if(!validJsonOfField(1, "device_sn", pJson["device_sn"], err, true))
            return false;
    }
    else
    {
        err="The device_sn column cannot be null";
        return false;
    }
    if(pJson.isMember("device_name"))
    {
        if(!validJsonOfField(2, "device_name", pJson["device_name"], err, true))
            return false;
    }
    else
    {
        err="The device_name column cannot be null";
        return false;
    }
    if(pJson.isMember("device_comment"))
    {
        if(!validJsonOfField(3, "device_comment", pJson["device_comment"], err, true))
            return false;
    }
    if(pJson.isMember("target_permission_level"))
    {
        if(!validJsonOfField(4, "target_permission_level", pJson["target_permission_level"], err, true))
            return false;
    }
    return true;
}
bool Device::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                std::string &err)
{
    if(pMasqueradingVector.size() != 5)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[2] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Device::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("device_id"))
    {
        if(!validJsonOfField(0, "device_id", pJson["device_id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("device_sn"))
    {
        if(!validJsonOfField(1, "device_sn", pJson["device_sn"], err, false))
            return false;
    }
    if(pJson.isMember("device_name"))
    {
        if(!validJsonOfField(2, "device_name", pJson["device_name"], err, false))
            return false;
    }
    if(pJson.isMember("device_comment"))
    {
        if(!validJsonOfField(3, "device_comment", pJson["device_comment"], err, false))
            return false;
    }
    if(pJson.isMember("target_permission_level"))
    {
        if(!validJsonOfField(4, "target_permission_level", pJson["target_permission_level"], err, false))
            return false;
    }
    return true;
}
bool Device::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                              const std::vector<std::string> &pMasqueradingVector,
                                              std::string &err)
{
    if(pMasqueradingVector.size() != 5)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Device::validJsonOfField(size_t index,
                              const std::string &fieldName,
                              const Json::Value &pJson,
                              std::string &err,
                              bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(!pJson.isUInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 100)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 100)";
                return false;
            }

            break;
        case 2:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 100)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 100)";
                return false;
            }

            break;
        case 3:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 1024)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 1024)";
                return false;
            }

            break;
        case 4:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isUInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
std::vector<Topic> Device::getTopics(const DbClientPtr &clientPtr) const {
    const static std::string sql = "select * from topic where target_device_id = ?";
    Result r(nullptr);
    {
        auto binder = *clientPtr << sql;
        binder << *deviceId_ << Mode::Blocking >>
            [&r](const Result &result) { r = result; };
        binder.exec();
    }
    std::vector<Topic> ret;
    ret.reserve(r.size());
    for (auto const &row : r)
    {
        ret.emplace_back(Topic(row));
    }
    return ret;
}

void Device::getTopics(const DbClientPtr &clientPtr,
                       const std::function<void(std::vector<Topic>)> &rcb,
                       const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from topic where target_device_id = ?";
    *clientPtr << sql
               << *deviceId_
               >> [rcb = std::move(rcb)](const Result &r){
                   std::vector<Topic> ret;
                   ret.reserve(r.size());
                   for (auto const &row : r)
                   {
                       ret.emplace_back(Topic(row));
                   }
                   rcb(ret);
               }
               >> ecb;
}
std::vector<SubscribeMap> Device::getSubscribes(const DbClientPtr &clientPtr) const {
    const static std::string sql = "select * from subscribe_map where target_device_id = ?";
    Result r(nullptr);
    {
        auto binder = *clientPtr << sql;
        binder << *deviceId_ << Mode::Blocking >>
            [&r](const Result &result) { r = result; };
        binder.exec();
    }
    std::vector<SubscribeMap> ret;
    ret.reserve(r.size());
    for (auto const &row : r)
    {
        ret.emplace_back(SubscribeMap(row));
    }
    return ret;
}

void Device::getSubscribes(const DbClientPtr &clientPtr,
                           const std::function<void(std::vector<SubscribeMap>)> &rcb,
                           const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from subscribe_map where target_device_id = ?";
    *clientPtr << sql
               << *deviceId_
               >> [rcb = std::move(rcb)](const Result &r){
                   std::vector<SubscribeMap> ret;
                   ret.reserve(r.size());
                   for (auto const &row : r)
                   {
                       ret.emplace_back(SubscribeMap(row));
                   }
                   rcb(ret);
               }
               >> ecb;
}
std::vector<UserDeviceAliasMap> Device::getAlias(const DbClientPtr &clientPtr) const {
    const static std::string sql = "select * from user_device_alias_map where target_device_id = ?";
    Result r(nullptr);
    {
        auto binder = *clientPtr << sql;
        binder << *deviceId_ << Mode::Blocking >>
            [&r](const Result &result) { r = result; };
        binder.exec();
    }
    std::vector<UserDeviceAliasMap> ret;
    ret.reserve(r.size());
    for (auto const &row : r)
    {
        ret.emplace_back(UserDeviceAliasMap(row));
    }
    return ret;
}

void Device::getAlias(const DbClientPtr &clientPtr,
                      const std::function<void(std::vector<UserDeviceAliasMap>)> &rcb,
                      const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from user_device_alias_map where target_device_id = ?";
    *clientPtr << sql
               << *deviceId_
               >> [rcb = std::move(rcb)](const Result &r){
                   std::vector<UserDeviceAliasMap> ret;
                   ret.reserve(r.size());
                   for (auto const &row : r)
                   {
                       ret.emplace_back(UserDeviceAliasMap(row));
                   }
                   rcb(ret);
               }
               >> ecb;
}
std::vector<UserDeviceActionMap> Device::getActions(const DbClientPtr &clientPtr) const {
    const static std::string sql = "select * from user_device_action_map where target_device_id = ?";
    Result r(nullptr);
    {
        auto binder = *clientPtr << sql;
        binder << *deviceId_ << Mode::Blocking >>
            [&r](const Result &result) { r = result; };
        binder.exec();
    }
    std::vector<UserDeviceActionMap> ret;
    ret.reserve(r.size());
    for (auto const &row : r)
    {
        ret.emplace_back(UserDeviceActionMap(row));
    }
    return ret;
}

void Device::getActions(const DbClientPtr &clientPtr,
                        const std::function<void(std::vector<UserDeviceActionMap>)> &rcb,
                        const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from user_device_action_map where target_device_id = ?";
    *clientPtr << sql
               << *deviceId_
               >> [rcb = std::move(rcb)](const Result &r){
                   std::vector<UserDeviceActionMap> ret;
                   ret.reserve(r.size());
                   for (auto const &row : r)
                   {
                       ret.emplace_back(UserDeviceActionMap(row));
                   }
                   rcb(ret);
               }
               >> ecb;
}
