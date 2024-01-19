/**
 *
 *  Topic.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Topic.h"
#include "Device.h"
#include "SubscribeMap.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::iot_server;

const std::string Topic::Cols::_topic_id = "topic_id";
const std::string Topic::Cols::_topic_name = "topic_name";
const std::string Topic::Cols::_topic_data = "topic_data";
const std::string Topic::Cols::_topic_qos = "topic_qos";
const std::string Topic::Cols::_target_device_id = "target_device_id";
const std::string Topic::primaryKeyName = "topic_id";
const bool Topic::hasPrimaryKey = true;
const std::string Topic::tableName = "topic";

const std::vector<typename Topic::MetaData> Topic::metaData_={
{"topic_id","uint32_t","int unsigned",4,1,1,1},
{"topic_name","std::string","varchar(255)",255,0,0,1},
{"topic_data","std::string","json",0,0,0,0},
{"topic_qos","std::string","enum('QOS0','QOS1','QOS2')",0,0,0,1},
{"target_device_id","uint32_t","int unsigned",4,0,0,1}
};
const std::string &Topic::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Topic::Topic(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["topic_id"].isNull())
        {
            topicId_=std::make_shared<uint32_t>(r["topic_id"].as<uint32_t>());
        }
        if(!r["topic_name"].isNull())
        {
            topicName_=std::make_shared<std::string>(r["topic_name"].as<std::string>());
        }
        if(!r["topic_data"].isNull())
        {
            topicData_=std::make_shared<std::string>(r["topic_data"].as<std::string>());
        }
        if(!r["topic_qos"].isNull())
        {
            topicQos_=std::make_shared<std::string>(r["topic_qos"].as<std::string>());
        }
        if(!r["target_device_id"].isNull())
        {
            targetDeviceId_=std::make_shared<uint32_t>(r["target_device_id"].as<uint32_t>());
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
            topicId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            topicName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            topicData_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            topicQos_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            targetDeviceId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
    }

}

Topic::Topic(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
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
            topicId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            topicName_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            topicData_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            topicQos_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            targetDeviceId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
}

Topic::Topic(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("topic_id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["topic_id"].isNull())
        {
            topicId_=std::make_shared<uint32_t>((uint32_t)pJson["topic_id"].asUInt64());
        }
    }
    if(pJson.isMember("topic_name"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["topic_name"].isNull())
        {
            topicName_=std::make_shared<std::string>(pJson["topic_name"].asString());
        }
    }
    if(pJson.isMember("topic_data"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["topic_data"].isNull())
        {
            topicData_=std::make_shared<std::string>(pJson["topic_data"].asString());
        }
    }
    if(pJson.isMember("topic_qos"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["topic_qos"].isNull())
        {
            topicQos_=std::make_shared<std::string>(pJson["topic_qos"].asString());
        }
    }
    if(pJson.isMember("target_device_id"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["target_device_id"].isNull())
        {
            targetDeviceId_=std::make_shared<uint32_t>((uint32_t)pJson["target_device_id"].asUInt64());
        }
    }
}

void Topic::updateByMasqueradedJson(const Json::Value &pJson,
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
            topicId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            topicName_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            topicData_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            topicQos_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            targetDeviceId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
}

void Topic::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("topic_id"))
    {
        if(!pJson["topic_id"].isNull())
        {
            topicId_=std::make_shared<uint32_t>((uint32_t)pJson["topic_id"].asUInt64());
        }
    }
    if(pJson.isMember("topic_name"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["topic_name"].isNull())
        {
            topicName_=std::make_shared<std::string>(pJson["topic_name"].asString());
        }
    }
    if(pJson.isMember("topic_data"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["topic_data"].isNull())
        {
            topicData_=std::make_shared<std::string>(pJson["topic_data"].asString());
        }
    }
    if(pJson.isMember("topic_qos"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["topic_qos"].isNull())
        {
            topicQos_=std::make_shared<std::string>(pJson["topic_qos"].asString());
        }
    }
    if(pJson.isMember("target_device_id"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["target_device_id"].isNull())
        {
            targetDeviceId_=std::make_shared<uint32_t>((uint32_t)pJson["target_device_id"].asUInt64());
        }
    }
}

const uint32_t &Topic::getValueOfTopicId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(topicId_)
        return *topicId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Topic::getTopicId() const noexcept
{
    return topicId_;
}
void Topic::setTopicId(const uint32_t &pTopicId) noexcept
{
    topicId_ = std::make_shared<uint32_t>(pTopicId);
    dirtyFlag_[0] = true;
}
const typename Topic::PrimaryKeyType & Topic::getPrimaryKey() const
{
    assert(topicId_);
    return *topicId_;
}

const std::string &Topic::getValueOfTopicName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(topicName_)
        return *topicName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Topic::getTopicName() const noexcept
{
    return topicName_;
}
void Topic::setTopicName(const std::string &pTopicName) noexcept
{
    topicName_ = std::make_shared<std::string>(pTopicName);
    dirtyFlag_[1] = true;
}
void Topic::setTopicName(std::string &&pTopicName) noexcept
{
    topicName_ = std::make_shared<std::string>(std::move(pTopicName));
    dirtyFlag_[1] = true;
}

const std::string &Topic::getValueOfTopicData() const noexcept
{
    const static std::string defaultValue = std::string();
    if(topicData_)
        return *topicData_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Topic::getTopicData() const noexcept
{
    return topicData_;
}
void Topic::setTopicData(const std::string &pTopicData) noexcept
{
    topicData_ = std::make_shared<std::string>(pTopicData);
    dirtyFlag_[2] = true;
}
void Topic::setTopicData(std::string &&pTopicData) noexcept
{
    topicData_ = std::make_shared<std::string>(std::move(pTopicData));
    dirtyFlag_[2] = true;
}
void Topic::setTopicDataToNull() noexcept
{
    topicData_.reset();
    dirtyFlag_[2] = true;
}

const std::string &Topic::getValueOfTopicQos() const noexcept
{
    const static std::string defaultValue = std::string();
    if(topicQos_)
        return *topicQos_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Topic::getTopicQos() const noexcept
{
    return topicQos_;
}
void Topic::setTopicQos(const std::string &pTopicQos) noexcept
{
    topicQos_ = std::make_shared<std::string>(pTopicQos);
    dirtyFlag_[3] = true;
}
void Topic::setTopicQos(std::string &&pTopicQos) noexcept
{
    topicQos_ = std::make_shared<std::string>(std::move(pTopicQos));
    dirtyFlag_[3] = true;
}

const uint32_t &Topic::getValueOfTargetDeviceId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(targetDeviceId_)
        return *targetDeviceId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Topic::getTargetDeviceId() const noexcept
{
    return targetDeviceId_;
}
void Topic::setTargetDeviceId(const uint32_t &pTargetDeviceId) noexcept
{
    targetDeviceId_ = std::make_shared<uint32_t>(pTargetDeviceId);
    dirtyFlag_[4] = true;
}

void Topic::updateId(const uint64_t id)
{
    topicId_ = std::make_shared<uint32_t>(static_cast<uint32_t>(id));
}

const std::vector<std::string> &Topic::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "topic_name",
        "topic_data",
        "topic_qos",
        "target_device_id"
    };
    return inCols;
}

void Topic::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getTopicName())
        {
            binder << getValueOfTopicName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTopicData())
        {
            binder << getValueOfTopicData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTopicQos())
        {
            binder << getValueOfTopicQos();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTargetDeviceId())
        {
            binder << getValueOfTargetDeviceId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Topic::updateColumns() const
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

void Topic::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getTopicName())
        {
            binder << getValueOfTopicName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTopicData())
        {
            binder << getValueOfTopicData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTopicQos())
        {
            binder << getValueOfTopicQos();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getTargetDeviceId())
        {
            binder << getValueOfTargetDeviceId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Topic::toJson() const
{
    Json::Value ret;
    if(getTopicId())
    {
        ret["topic_id"]=getValueOfTopicId();
    }
    else
    {
        ret["topic_id"]=Json::Value();
    }
    if(getTopicName())
    {
        ret["topic_name"]=getValueOfTopicName();
    }
    else
    {
        ret["topic_name"]=Json::Value();
    }
    if(getTopicData())
    {
        ret["topic_data"]=getValueOfTopicData();
    }
    else
    {
        ret["topic_data"]=Json::Value();
    }
    if(getTopicQos())
    {
        ret["topic_qos"]=getValueOfTopicQos();
    }
    else
    {
        ret["topic_qos"]=Json::Value();
    }
    if(getTargetDeviceId())
    {
        ret["target_device_id"]=getValueOfTargetDeviceId();
    }
    else
    {
        ret["target_device_id"]=Json::Value();
    }
    return ret;
}

Json::Value Topic::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 5)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getTopicId())
            {
                ret[pMasqueradingVector[0]]=getValueOfTopicId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getTopicName())
            {
                ret[pMasqueradingVector[1]]=getValueOfTopicName();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getTopicData())
            {
                ret[pMasqueradingVector[2]]=getValueOfTopicData();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getTopicQos())
            {
                ret[pMasqueradingVector[3]]=getValueOfTopicQos();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getTargetDeviceId())
            {
                ret[pMasqueradingVector[4]]=getValueOfTargetDeviceId();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getTopicId())
    {
        ret["topic_id"]=getValueOfTopicId();
    }
    else
    {
        ret["topic_id"]=Json::Value();
    }
    if(getTopicName())
    {
        ret["topic_name"]=getValueOfTopicName();
    }
    else
    {
        ret["topic_name"]=Json::Value();
    }
    if(getTopicData())
    {
        ret["topic_data"]=getValueOfTopicData();
    }
    else
    {
        ret["topic_data"]=Json::Value();
    }
    if(getTopicQos())
    {
        ret["topic_qos"]=getValueOfTopicQos();
    }
    else
    {
        ret["topic_qos"]=Json::Value();
    }
    if(getTargetDeviceId())
    {
        ret["target_device_id"]=getValueOfTargetDeviceId();
    }
    else
    {
        ret["target_device_id"]=Json::Value();
    }
    return ret;
}

bool Topic::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("topic_id"))
    {
        if(!validJsonOfField(0, "topic_id", pJson["topic_id"], err, true))
            return false;
    }
    if(pJson.isMember("topic_name"))
    {
        if(!validJsonOfField(1, "topic_name", pJson["topic_name"], err, true))
            return false;
    }
    else
    {
        err="The topic_name column cannot be null";
        return false;
    }
    if(pJson.isMember("topic_data"))
    {
        if(!validJsonOfField(2, "topic_data", pJson["topic_data"], err, true))
            return false;
    }
    if(pJson.isMember("topic_qos"))
    {
        if(!validJsonOfField(3, "topic_qos", pJson["topic_qos"], err, true))
            return false;
    }
    if(pJson.isMember("target_device_id"))
    {
        if(!validJsonOfField(4, "target_device_id", pJson["target_device_id"], err, true))
            return false;
    }
    else
    {
        err="The target_device_id column cannot be null";
        return false;
    }
    return true;
}
bool Topic::validateMasqueradedJsonForCreation(const Json::Value &pJson,
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
        else
        {
            err="The " + pMasqueradingVector[4] + " column cannot be null";
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
bool Topic::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("topic_id"))
    {
        if(!validJsonOfField(0, "topic_id", pJson["topic_id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("topic_name"))
    {
        if(!validJsonOfField(1, "topic_name", pJson["topic_name"], err, false))
            return false;
    }
    if(pJson.isMember("topic_data"))
    {
        if(!validJsonOfField(2, "topic_data", pJson["topic_data"], err, false))
            return false;
    }
    if(pJson.isMember("topic_qos"))
    {
        if(!validJsonOfField(3, "topic_qos", pJson["topic_qos"], err, false))
            return false;
    }
    if(pJson.isMember("target_device_id"))
    {
        if(!validJsonOfField(4, "target_device_id", pJson["target_device_id"], err, false))
            return false;
    }
    return true;
}
bool Topic::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
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
bool Topic::validJsonOfField(size_t index,
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
            if(pJson.isString() && pJson.asString().length() > 255)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 255)";
                return false;
            }

            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 3:
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
Device Topic::getDevice(const DbClientPtr &clientPtr) const {
    const static std::string sql = "select * from device where device_id = ?";
    Result r(nullptr);
    {
        auto binder = *clientPtr << sql;
        binder << *targetDeviceId_ << Mode::Blocking >>
            [&r](const Result &result) { r = result; };
        binder.exec();
    }
    if (r.size() == 0)
    {
        throw UnexpectedRows("0 rows found");
    }
    else if (r.size() > 1)
    {
        throw UnexpectedRows("Found more than one row");
    }
    return Device(r[0]);
}

void Topic::getDevice(const DbClientPtr &clientPtr,
                      const std::function<void(Device)> &rcb,
                      const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from device where device_id = ?";
    *clientPtr << sql
               << *targetDeviceId_
               >> [rcb = std::move(rcb), ecb](const Result &r){
                    if (r.size() == 0)
                    {
                        ecb(UnexpectedRows("0 rows found"));
                    }
                    else if (r.size() > 1)
                    {
                        ecb(UnexpectedRows("Found more than one row"));
                    }
                    else
                    {
                        rcb(Device(r[0]));
                    }
               }
               >> ecb;
}
std::vector<SubscribeMap> Topic::getSubscribes(const DbClientPtr &clientPtr) const {
    const static std::string sql = "select * from subscribe_map where target_topic_id = ?";
    Result r(nullptr);
    {
        auto binder = *clientPtr << sql;
        binder << *topicId_ << Mode::Blocking >>
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

void Topic::getSubscribes(const DbClientPtr &clientPtr,
                          const std::function<void(std::vector<SubscribeMap>)> &rcb,
                          const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from subscribe_map where target_topic_id = ?";
    *clientPtr << sql
               << *topicId_
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
