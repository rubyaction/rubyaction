# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
RubyAction::Stage << background

# crate
crate = RubyAction::Bitmap.new RubyAction::Texture.new "crate.png"
crate.anchor = [0.5, 0.5]

# render target
rt = RubyAction::RenderTarget.new 800, 600

# bitmap
bitmap = RubyAction::Bitmap.new rt
RubyAction::Stage << bitmap

frame = 0
RubyAction::Stage.on :enter_frame do |dt|
  r = Math::sin(frame * 0.03) * 0.3 + 0.7
  g = Math::sin(frame * 0.04) * 0.3 + 0.7
  b = Math::sin(frame * 0.05) * 0.3 + 0.7
  frame = frame + 1

  # update crate
  crate.color = [r, g, b, 1]
  crate.x += dt * 50
  crate.y += dt * 40
  crate.rotation += dt * 50

  # draw crate
  rt.draw crate
end
