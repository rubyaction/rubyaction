World
-----

.. rb:module:: RubyAction::Physics

.. rb:class:: World

  The :rb:meth:`World` class inherits from the following class: :rb:meth:`EventDispatcher <RubyAction::EventDispatcher>`.
  The :rb:meth:`World` class manages all physics entities and dynamic simulation.

  It is possible to create and manage more than one :rb:meth:`World` instance.


  .. rb:classmethod:: new(gravityx, gravityy, do_sleep)

    Creates a new :rb:meth:`World` object. You can create more then one :rb:meth:`World` object to manage independent worlds.

    **Parameters:**
      - **gravityx**: (number) the x component the gravity
      - **gravityy**: (number) the y component the gravity
      - **do_sleep**: (boolean, default = true) improve performance by not simulating inactive bodies


    **Example:**

    .. code-block:: ruby

      RubyAction::Physics::World.new(0, -10, false)


  .. rb:method:: clear_forces!

    Call this after you are done with time steps to clear the forces. You normally call this after each call to :rb:meth:`World#step`,
    unless you are performing sub-steps. By default, forces will be automatically cleared, so you don't need to call this function.


    **Example:**

    .. code-block:: ruby

      world.clear_forces!


  .. rb:method:: gravity

    Returns the gravity vector.

    **Returns:**
      - **gravity**: (array) the gravity vector

    **Example:**

    .. code-block:: ruby

      gravityx, gravityy = world.gravity


  .. rb:method:: gravity=(gravity)

    Sets the gravity vector.

    **Parameters:**
      - **gravity**: (array) the gravity vector

    **Example:**

    .. code-block:: ruby

      world.gravity = [0, 10] # inverse gravity


  .. rb:method:: step(time_step, velocity_iterations, position_iterations)

    Take a time step. This performs collision detection, integration, and constraint solution.

    **Parameters:**
      - **time_step**: (number) the amount of time to simulate, this should not vary
      - **velocity_iterations**: (number) for the velocity constraint solver
      - **position_iterations**: (number) for the position constraint solver


    **Example:**

    .. code-block:: ruby

      RubyAction::Stage.on :enter_frame do |dt|
        world.step dt, 8, 8
      end
