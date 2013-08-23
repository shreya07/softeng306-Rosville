
(cl:in-package :asdf)

(defsystem "se306_example-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "IdentityReply" :depends-on ("_package_IdentityReply"))
    (:file "_package_IdentityReply" :depends-on ("_package"))
    (:file "Custom" :depends-on ("_package_Custom"))
    (:file "_package_Custom" :depends-on ("_package"))
    (:file "IdentityRequest" :depends-on ("_package_IdentityRequest"))
    (:file "_package_IdentityRequest" :depends-on ("_package"))
  ))