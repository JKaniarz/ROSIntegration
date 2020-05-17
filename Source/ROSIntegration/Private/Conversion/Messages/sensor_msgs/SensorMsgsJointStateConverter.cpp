#include "Conversion/Messages/sensor_msgs/SensorMsgsJointStateConverter.h"

USensorMsgsJointStateConverter::USensorMsgsJointStateConverter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	_MessageType = "sensor_msgs/JointState";
}

bool USensorMsgsJointStateConverter::ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg>& BaseMsg) {
	std::unique_ptr<ROSMessages::sensor_msgs::JointState> joint_state_msg = std::make_unique<ROSMessages::sensor_msgs::JointState>();
	BaseMsg = TSharedPtr<FROSBaseMsg>(joint_state_msg.get());

	const FString key = "msg";
	bool KeyFound = false;

	KeyFound = UStdMsgsHeaderConverter::_bson_extract_child_header(message->full_msg_bson_, TEXT("msg.header"), &joint_state_msg->header);
	if (!KeyFound) return false;

	joint_state_msg->name = UBaseMessageConverter::GetTArrayFromBSON<FString>(key + ".name", message->full_msg_bson_, KeyFound, [](FString subKey, bson_t* subMsg, bool& subKeyFound) { return GetFStringFromBSON(subKey, subMsg, subKeyFound, false); });
	if (!KeyFound) return false;

	joint_state_msg->position = UBaseMessageConverter::GetDoubleTArrayFromBSON(key + ".position", message->full_msg_bson_, KeyFound);
	if (!KeyFound) return false;

	joint_state_msg->velocity = UBaseMessageConverter::GetDoubleTArrayFromBSON(key + ".velocity", message->full_msg_bson_, KeyFound);
	if (!KeyFound) return false;

	joint_state_msg->effort = UBaseMessageConverter::GetDoubleTArrayFromBSON(key + ".effort", message->full_msg_bson_, KeyFound);

	return KeyFound;
}

bool USensorMsgsJointStateConverter::ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message) {
	auto JointStateMessage = StaticCastSharedPtr<ROSMessages::sensor_msgs::JointState>(BaseMsg);
	
	*message = new bson_t;
	bson_init(*message);

	UStdMsgsHeaderConverter::_bson_append_header(*message, &(JointStateMessage->header));

	// parent class utility methods
	UBaseMessageConverter::_bson_append_double_tarray(*message, "position", JointStateMessage->position); 
	UBaseMessageConverter::_bson_append_double_tarray(*message, "velocity", JointStateMessage->velocity);
	UBaseMessageConverter::_bson_append_double_tarray(*message, "effort", JointStateMessage->effort);

	return true;
}