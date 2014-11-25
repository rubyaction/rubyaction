# This is a tweening library for Ruby.  It has no dependencies, but was
# designed with Gosu in mind.

# This is mostly an implementation of Robert Penner's easing equations
# More information on the equations can be found here:
#   http://www.robertpenner.com/easing/
#
# UziMonkey <michael.c.morin@gmail.com>

class Tween < RubyAction::EventDispatcher
  attr_reader :done
  attr_reader :easer

  def initialize(start, finish, easer, duration)
    super
    @start, @finish = start, finish
    @easer, @duration = easer, duration

    unless @start.is_a? Enumerable
      @start = [@start]
    end

    unless @finish.is_a? Enumerable
      @finish = [@finish]
    end

    @time = 0
    @done = false
  end

  def update(delta)
    return if @done
    @time += delta
    if @time > @duration
      @time = @duration
      @done = true
      self.dispatch :complete
    end
  end

  def [](idx)
    @easer.ease(
      @time,
      @start[idx],
      (@finish[idx] - @start[idx]),
      @duration
    )
  end

  def value; self[0]; end
  def x; self[0]; end
  def y; self[1]; end
  def z; self[2]; end

  # In the following ease methods:
  #  st = start
  #  t = time
  #  d = duration
  #  ch = change

  # I know, these are quite messy.  I don't know 100% what's going on in many
  # of them, but they're translated from Penner's ActionScript code which was
  # uncommented and rather indecipherable.
  module Linear
    def self.ease(t, st, ch, d)
      ch * t / d + st
    end
  end

  module Sine
    module In
      def self.ease(t, st, ch, d)
        -ch * Math.cos(t / d * (Math::PI / 2)) + ch + st
      end
    end

    module Out
      def self.ease(t, st, ch, d)
        ch * Math.sin(t / d * (Math::PI / 2)) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        -ch / 2 * (Math.cos(Math::PI * t / d) - 1) + st
      end
    end
  end

  module Circ
    module In
      def self.ease(t, st, ch, d)
        -ch * (Math.sqrt(1 - (t/d) * t/d) - 1) + st
      end
    end

    module Out
      def self.ease(t, st, ch, d)
        t = t/d - 1
        ch * Math.sqrt(1 - t * t) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        if (t /= d/2.0) < 1
          return -ch / 2 * (Math.sqrt(1 - t*t) - 1) + st
        else
          return ch / 2 * (Math.sqrt(1 - (t -= 2) * t) + 1) + st
        end
      end
    end
  end

  module Bounce
    module Out
      def self.ease(t, st, ch, d)
        if (t /= d) < (1/2.75)
          ch * (7.5625 * t * t) + st
        elsif t < (2 / 2.75)
          ch * (7.5625 * (t -= (1.5 / 2.75)) * t + 0.75) + st
        elsif t < (2.5 / 2.75)
          ch * (7.5625 * (t -= (2.25 / 2.75)) * t + 0.9375) + st
        else
          ch * (7.5625 * (t -= (2.625 / 2.75)) * t + 0.984375) + st
        end
      end
    end

    module In
      def self.ease(t, st, ch, d)
        ch - Tween::Bounce::Out.ease(d-t, 0, ch, d) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        if t < d/2.0
          Tween::Bounce::In.ease(t*2.0, 0, ch, d) * 0.5 + st
        else
          Tween::Bounce::Out.ease(t*2.0 - d, 0, ch, d) * 0.5 + ch * 0.5 + st
        end
      end
    end
  end

  module Back
    module In
      def self.ease(t, st, ch, d, s=1.70158)
        ch * (t/=d) * t * ((s+1) * t - s) + st
      end
    end

    module Out
      def self.ease(t, st, ch, d, s=1.70158)
        ch * ((t=t/d-1) * t * ((s+1) * t + s) + 1) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d, s=1.70158)
        if (t /= d/2.0) < 1
          ch / 2.0 * (t * t * (((s *= (1.525)) + 1) * t - s)) + st
        else
          ch / 2.0 * ((t -= 2) * t * (((s *= (1.525)) + 1) * t + s) + 2) + st
        end
      end
    end
  end

  module Cubic
    module In
      def self.ease(t, st, ch, d)
        ch * (t /= d) * t * t + st
      end
    end

    module Out
      def self.ease(t, st, ch, d)
        ch * ((t = t / d.to_f - 1) * t * t + 1) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        if (t /= d / 2.0) < 1
          ch / 2.0 * t * t * t + st
        else
          ch / 2.0 * ((t -= 2) * t * t + 2) + st
        end
      end
    end
  end

  module Expo
    module In
      def self.ease(t, st, ch, d)
        if t == 0
          st
        else
          ch * (2 ** (10 * (t / d.to_f - 1))) + st
        end
      end
    end

    module Out
      def self.ease(t, st, ch, d)
        if t == d
          st + ch
        else
          ch * (-(2 ** (-10 * t / d.to_f)) + 1) + st
        end
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        if t == 0
          st
        elsif t == d
          st + ch
        elsif (t /= d / 2.0) < 1
          ch / 2.0 * (2 ** (10 * (t - 1))) + st
        else
          ch / 2.0 * (-(2 ** (-10 * (t -= 1))) + 2) + st
        end
      end
    end
  end

  module Quad
    module In
      def self.ease(t, st, ch, d)
        ch * (t /= d.to_f) * t + st
      end
    end

    module Out
      def self.ease(t, st, ch, d)
        -ch * (t /= d.to_f) * (t - 2) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        if (t /= d / 2.0) < 1
          ch / 2.0 * t * t + st
        else
          -ch / 2.0 * ((t -= 1) * (t - 2) - 1) + st
        end
      end
    end
  end

  module Quart
    module In
      def self.ease(t, st, ch, d)
        ch * (t /= d.to_f) * t * t * t + st
      end
    end

    module Out
      def self.ease(t, st, ch, d)
        -ch * ((t = t / d.to_f - 1) * t * t * t - 1) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        if (t /= d / 2.0) < 1
          ch / 2.0 * t * t * t * t + st
        else
          -ch / 2.0 * ((t -= 2) * t * t * t - 2) + st
        end
      end
    end
  end

  module Quint
    module In
      def self.ease(t, st, ch, d)
        ch * (t /= d.to_f) * t * t * t * t + st
      end
    end

    module Out
      def self.ease(t, st, ch, d)
        ch * ((t = t / d.to_f - 1) * t * t * t * t + 1) + st
      end
    end

    module InOut
      def self.ease(t, st, ch, d)
        if (t /= d / 2.0) < 1
          ch / 2.0 * t * t * t * t * t + st
        else
          ch / 2.0 * ((t -= 2) * t * t * t * t + 2) + st
        end
      end
    end
  end

  module Elastic
    module In
      def self.ease(t, st, ch, d, a = 5, p = 0)
        s = 0

        if t == 0
          return st
        elsif (t /= d.to_f) >= 1
          return st + ch
        end

        p = d * 0.3 if p == 0

        if (a == 0) || (a < ch.abs)
          a = ch
          s = p / 4.0
        else
          s = p / (2 * Math::PI) * Math.asin(ch / a.to_f)
        end

        -(a * (2 ** (10 * (t -= 1))) * Math.sin( (t * d - s) * (2 * Math::PI) / p)) + st
      end
    end

    module Out
      def self.ease(t, st, ch, d, a = 0.1, p = 0)
        s = 0

        if t == 0
          return st
        elsif (t /= d.to_f) >= 1
          return st + ch
        end

        p = d * 0.3 if p == 0

        if (a == 0) || (a < ch.abs)
          a = ch
          s = p / 4.0
        else
          s = p / (2 * Math::PI) * Math.asin(ch / a.to_f)
        end

        a * (2 ** (-10 * t)) * Math.sin((t * d - s) * (2 * Math::PI) / p.to_f) + ch + st
      end
    end
  end

end
