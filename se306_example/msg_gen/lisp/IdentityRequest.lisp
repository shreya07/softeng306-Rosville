; Auto-generated. Do not edit!


(cl:in-package se306_example-msg)


;//! \htmlinclude IdentityRequest.msg.html

(cl:defclass <IdentityRequest> (roslisp-msg-protocol:ros-message)
  ((sender
    :reader sender
    :initarg :sender
    :type cl:string
    :initform "")
   (px
    :reader px
    :initarg :px
    :type cl:float
    :initform 0.0)
   (py
    :reader py
    :initarg :py
    :type cl:float
    :initform 0.0))
)

(cl:defclass IdentityRequest (<IdentityRequest>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <IdentityRequest>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'IdentityRequest)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name se306_example-msg:<IdentityRequest> is deprecated: use se306_example-msg:IdentityRequest instead.")))

(cl:ensure-generic-function 'sender-val :lambda-list '(m))
(cl:defmethod sender-val ((m <IdentityRequest>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader se306_example-msg:sender-val is deprecated.  Use se306_example-msg:sender instead.")
  (sender m))

(cl:ensure-generic-function 'px-val :lambda-list '(m))
(cl:defmethod px-val ((m <IdentityRequest>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader se306_example-msg:px-val is deprecated.  Use se306_example-msg:px instead.")
  (px m))

(cl:ensure-generic-function 'py-val :lambda-list '(m))
(cl:defmethod py-val ((m <IdentityRequest>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader se306_example-msg:py-val is deprecated.  Use se306_example-msg:py instead.")
  (py m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <IdentityRequest>) ostream)
  "Serializes a message object of type '<IdentityRequest>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sender))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sender))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'px))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'py))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <IdentityRequest>) istream)
  "Deserializes a message object of type '<IdentityRequest>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sender) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sender) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'px) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'py) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<IdentityRequest>)))
  "Returns string type for a message object of type '<IdentityRequest>"
  "se306_example/IdentityRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'IdentityRequest)))
  "Returns string type for a message object of type 'IdentityRequest"
  "se306_example/IdentityRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<IdentityRequest>)))
  "Returns md5sum for a message object of type '<IdentityRequest>"
  "b05d0f8eb57ddf35a356dc69ad6364e7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'IdentityRequest)))
  "Returns md5sum for a message object of type 'IdentityRequest"
  "b05d0f8eb57ddf35a356dc69ad6364e7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<IdentityRequest>)))
  "Returns full string definition for message of type '<IdentityRequest>"
  (cl:format cl:nil "string sender~%float32 px~%float32 py~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'IdentityRequest)))
  "Returns full string definition for message of type 'IdentityRequest"
  (cl:format cl:nil "string sender~%float32 px~%float32 py~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <IdentityRequest>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'sender))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <IdentityRequest>))
  "Converts a ROS message object to a list"
  (cl:list 'IdentityRequest
    (cl:cons ':sender (sender msg))
    (cl:cons ':px (px msg))
    (cl:cons ':py (py msg))
))
