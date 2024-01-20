/**
 *
 *  UserDeviceActionMap.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace iot_server
{
class Device;
class Topic;
class User;

class UserDeviceActionMap
{
  public:
    struct Cols
    {
        static const std::string _action_map_id;
        static const std::string _target_user_id;
        static const std::string _target_device_id;
        static const std::string _action_name;
        static const std::string _action_target_topic_id;
        static const std::string _action_json;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = uint32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit UserDeviceActionMap(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit UserDeviceActionMap(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    UserDeviceActionMap(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    UserDeviceActionMap() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column action_map_id  */
    ///Get the value of the column action_map_id, returns the default value if the column is null
    const uint32_t &getValueOfActionMapId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t> &getActionMapId() const noexcept;
    ///Set the value of the column action_map_id
    void setActionMapId(const uint32_t &pActionMapId) noexcept;

    /**  For column target_user_id  */
    ///Get the value of the column target_user_id, returns the default value if the column is null
    const uint32_t &getValueOfTargetUserId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t> &getTargetUserId() const noexcept;
    ///Set the value of the column target_user_id
    void setTargetUserId(const uint32_t &pTargetUserId) noexcept;

    /**  For column target_device_id  */
    ///Get the value of the column target_device_id, returns the default value if the column is null
    const uint32_t &getValueOfTargetDeviceId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t> &getTargetDeviceId() const noexcept;
    ///Set the value of the column target_device_id
    void setTargetDeviceId(const uint32_t &pTargetDeviceId) noexcept;

    /**  For column action_name  */
    ///Get the value of the column action_name, returns the default value if the column is null
    const std::string &getValueOfActionName() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getActionName() const noexcept;
    ///Set the value of the column action_name
    void setActionName(const std::string &pActionName) noexcept;
    void setActionName(std::string &&pActionName) noexcept;

    /**  For column action_target_topic_id  */
    ///Get the value of the column action_target_topic_id, returns the default value if the column is null
    const uint32_t &getValueOfActionTargetTopicId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t> &getActionTargetTopicId() const noexcept;
    ///Set the value of the column action_target_topic_id
    void setActionTargetTopicId(const uint32_t &pActionTargetTopicId) noexcept;

    /**  For column action_json  */
    ///Get the value of the column action_json, returns the default value if the column is null
    const std::string &getValueOfActionJson() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getActionJson() const noexcept;
    ///Set the value of the column action_json
    void setActionJson(const std::string &pActionJson) noexcept;
    void setActionJson(std::string &&pActionJson) noexcept;


    static size_t getColumnNumber() noexcept {  return 6;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
    User getUser(const drogon::orm::DbClientPtr &clientPtr) const;
    void getUser(const drogon::orm::DbClientPtr &clientPtr,
                 const std::function<void(User)> &rcb,
                 const drogon::orm::ExceptionCallback &ecb) const;
    Device getDevice(const drogon::orm::DbClientPtr &clientPtr) const;
    void getDevice(const drogon::orm::DbClientPtr &clientPtr,
                   const std::function<void(Device)> &rcb,
                   const drogon::orm::ExceptionCallback &ecb) const;
    Topic getTopic(const drogon::orm::DbClientPtr &clientPtr) const;
    void getTopic(const drogon::orm::DbClientPtr &clientPtr,
                  const std::function<void(Topic)> &rcb,
                  const drogon::orm::ExceptionCallback &ecb) const;
  private:
    friend drogon::orm::Mapper<UserDeviceActionMap>;
    friend drogon::orm::BaseBuilder<UserDeviceActionMap, true, true>;
    friend drogon::orm::BaseBuilder<UserDeviceActionMap, true, false>;
    friend drogon::orm::BaseBuilder<UserDeviceActionMap, false, true>;
    friend drogon::orm::BaseBuilder<UserDeviceActionMap, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<UserDeviceActionMap>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<uint32_t> actionMapId_;
    std::shared_ptr<uint32_t> targetUserId_;
    std::shared_ptr<uint32_t> targetDeviceId_;
    std::shared_ptr<std::string> actionName_;
    std::shared_ptr<uint32_t> actionTargetTopicId_;
    std::shared_ptr<std::string> actionJson_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[6]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where action_map_id = ?";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where action_map_id = ?";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "action_map_id,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "target_user_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "target_device_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "action_name,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "action_target_topic_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "action_json,";
            ++parametersCount;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        sql +="default,";
        if(dirtyFlag_[1])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[2])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[3])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[4])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[5])
        {
            sql.append("?,");

        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        sql.append(1, ')');
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace iot_server
} // namespace drogon_model
