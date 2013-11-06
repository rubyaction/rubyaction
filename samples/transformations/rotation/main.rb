# background
background = RubyAction::Bitmap.new RubyAction::Texture.new "background.jpg"
background.position = [400, 300]
RubyAction::Stage << background

# crate
crate = RubyAction::Bitmap.new RubyAction::Texture.new "crate.png"
crate.position = [400, 300]

crate.on :enter_frame do |dt|
  crate.rotation += dt * 100
end

RubyAction::Stage << crate
