
(cl:in-package :asdf)

(defsystem "se306_example-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Grass" :depends-on ("_package_Grass"))
    (:file "_package_Grass" :depends-on ("_package"))
  ))