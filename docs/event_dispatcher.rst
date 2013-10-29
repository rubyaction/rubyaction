=================
 EventDispatcher
=================

.. rb:module:: RubyAction

.. rb:class:: EventDispatcher

  All classes that dispatch events inherit from :rb:meth:`EventDispatcher`.
  The target of an event is a listener function and an optional data value.
  When an event is dispatched, the registered function is called.

  If the optional data value is given, it is used as a first parameter while calling the listener function.
  Event dispatching and event targets are the core part of the RubyAction event model.

  Different event types (such as :rb:meth:`Event.ENTER_FRAME`, :rb:meth:`Event.TOUCHES_BEGIN` or :rb:meth:`Event.MOUSE_DOWN`) flow through the scene tree hierarchy differently.
  When a touch or mouse event occurs, RubyAction dispatches an event object into the event flow from the root of the scene tree.
  On the other hand, :rb:meth:`Event.ENTER_FRAME` event is dispatched to all :rb:meth:`Sprite` objects.

  .. code:: ruby

    dispatcher = RubyAction::EventDispatcher.new
    dispatcher.on :event, { puts 'Event received' }
    dispatcher.dispatch :event

  If you want to define a class that dispatches events, you can inherit your class from EventDispatcher.


  .. rb:classmethod:: new()

    Create a new remote object stub.

    obj is the (local) object we want to create a stub for. Normally this is nil.
    uri is the URI of the remote object that this will be a stub for.

    *Parameters:*
      - **primeiro** - iqweiuq qwetiqwte iqw asdsajhdgjhasg dhjsag dhjasg ``dhjasg`` hjdg `asjhd` _gjashg_ djasg djhgas jdg asjdg jasgd jas gdjasgjdh gasjhd gajsd gjas dgj
      - **segundo** - asjdas

  .. rb:method:: new_with_uri(uri)

    Create a new DRbObject from a URI alone.

  .. rb:method:: method_missing(msg_id, *a, &b)

    Routes method calls to the referenced object.
