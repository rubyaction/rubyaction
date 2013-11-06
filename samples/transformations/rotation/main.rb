texture = RubyAction::Texture.new "crate.png"

crate = RubyAction::Bitmap.new texture
crate.position = [400, 300]

crate.on :enter_frame do |dt|
  crate.rotation += dt * 100
end

RubyAction::Stage << crate
