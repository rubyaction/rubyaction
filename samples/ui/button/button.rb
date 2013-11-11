#
# A generic button class
#
# Copyright (c) 2013-2014 TangerinaGames
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

class Button < RubyAction::Sprite

  def initialize up, down
    super
    self.size = up.size

    @up = up
    @down = down

    @focus = false

    update_visual_state false

    on :mouse_up, :on_mouse_up
    on :mouse_down, :on_mouse_down
    on :mouse_move, :on_mouse_move
  end

  def update_visual_state down
    if down then
      remove_child @up
      add_child @down
    else
      remove_child @down
      add_child @up
    end
  end

  def on_mouse_up button, x, y
    if @focus then
      @focus = false
      update_visual_state false
      dispatch :click
    end
  end

  def on_mouse_down button, x, y
    if collide?(x, y) then
      @focus = true
      update_visual_state true
    end
  end

  def on_mouse_move x, y
    if @focus then
      unless collide?(x, y) then
        @focus = false
        update_visual_state false
      end
    end
  end

end
