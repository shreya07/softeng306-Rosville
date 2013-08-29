; Auto-generated. Do not edit!


(cl:in-package se306_example-msg)


;//! \htmlinclude Custom.msg.html

(cl:defclass <Custom> (roslisp-msg-protocol:ros-message)
  ((robot_name
    :reader robot_name
    :initarg :robot_name
    :type cl:string
    :initform "")
   (px
    :reader px
    :initarg :px
    :type cl:integer
    :initform 0)
   (py
    :reader py
    :initarg :py
    :type cl:integer
    :initform 0))
)

(cl:defclass Custom (<Custom>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Custom>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Custom)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name se306_example-msg:<Custom> is deprecated: use se306_example-msg:Custom instead.")))

(cl:ensure-generic-function 'robot_name-val :lambda-list '(m))
(cl:defmethod robot_name-val ((m <Custom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader se306_example-msg:robot_name-val is deprecated.  Use se306_example-msg:robot_name instead.")
  (robot_name m))

(cl:ensure-generic-function 'px-val :lambda-list '(m))
(cl:defmethod px-val ((m <Custom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader se306_example-msg:px-val is deprecated.  Use se306_example-msg:px instead.")
  (px m))

(cl:ensure-generic-function 'py-val :lambda-list '(m))
(cl:defmethod py-val ((m <Custom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader se306_example-msg:py-val is deprecated.  Use se306_example-msg:py instead.")
  (py m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Custom>) ostream)
  "Serializes a message object of type '<Custom>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'robot_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'robot_name))
  (cl:let* ((signed (cl:slot-value msg 'px)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'py)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Custom>) istream)
  "Deserializes a message object of type '<Custom>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'robot_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'px) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'py) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Custom>)))
  "Returns string type for a message object of type '<Custom>"
  "se306_example/Custom")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Custom)))
  "Returns string type for a message object of type 'Custom"
  "se306_example/Custom")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Custom>)))
  "Returns md5sum for a message object of type '<Custom>"
  "82eb8202e95e71eede1f9a296896b7d3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Custom)))
  "Returns md5sum for a message object of type 'Custom"
  "82eb8202e95e71eede1f9a296896b7d3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Custom>)))
  "Returns full string definition for message of type '<Custom>"
  (cl:format cl:nil "string robot_name~%int64 px~%int64 py~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Custom)))
  "Returns full string definition for message of type 'Custom"
  (cl:format cl:nil "string robot_name~%int64 px~%int64 py~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Custom>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'robot_name))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Custom>))
  "Converts a ROS message object to a list"
  (cl:list 'Custom
    (cl:cons ':robot_name (robot_name msg))
    (cl:cons ':px (px msg))
    (cl:cons ':py (py msg))
))
