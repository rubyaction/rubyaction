# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
RubyAction::Stage << background

# crate
crate = RubyAction::Bitmap.new RubyAction::Texture.new "crate.png"

# render target
rt = RubyAction::RenderTarget.new crate.width * 2, crate.height * 2

# bitmap
bitmap = RubyAction::Bitmap.new rt
bitmap.position = [200, 100]
bitmap.scale = [2, 2]
RubyAction::Stage << bitmap

frame = 0
RubyAction::Stage.on :enter_frame do |dt|
  r = Math::sin(frame * 0.03) * 0.3 + 0.7
  g = Math::sin(frame * 0.04) * 0.3 + 0.7
  b = Math::sin(frame * 0.05) * 0.3 + 0.7
  frame = frame + 1

  # update crate
  crate.color = [r * 255, g * 255, b * 255, 255]
  crate.x += dt * 10
  crate.y += dt * 10

  # draw crate
  rt.draw crate
end
