#include "Conversion/Messages/geometry_msgs/GeometryMsgsTransformStampedConverter.h"

#include "Conversion/Messages/std_msgs/StdMsgsHeaderConverter.h"
#include "geometry_msgs/TransformStamped.h"


UGeometryMsgsTransformStampedConverter::UGeometryMsgsTransformStampedConverter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	_MessageType = "geometry_msgs/TransformStamped";
}

bool UGeometryMsgsTransformStampedConverter::ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg)
{
    UE_LOG(LogTemp, Warning, TEXT("ROSIntegration: TransformStamped received"));
    auto p = new ROSMessages::geometry_msgs::TransformStamped;
    BaseMsg = TSharedPtr<FROSBaseMsg>(p);
    return (_bson_extract_child_transform_stamped(message->full_msg_bson_, "msg", p));
}

bool UGeometryMsgsTransformStampedConverter::ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message)
{
	auto TransformStamped = StaticCastSharedPtr<ROSMessages::geometry_msgs::TransformStamped>(BaseMsg);

	*message = bson_new();
	UStdMsgsHeaderConverter::_bson_append_child_header(*message, "header", &(TransformStamped->header));
	BSON_APPEND_UTF8(*message, "child_frame_id", TCHAR_TO_UTF8(*TransformStamped->child_frame_id));
	UGeometryMsgsTransformConverter::_bson_append_child_transform(*message, "transform", &(TransformStamped->transform));

	return true;
}
