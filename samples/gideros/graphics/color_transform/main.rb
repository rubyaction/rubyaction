module Game
  include RubyAction

  # add all the images to the stage
  bitmap = Bitmap.new(Texture.new("bird.png"))
  bitmap.position = [300, 112]
  Stage << bitmap

  redbar = Bitmap.new(Texture.new("red-bar.png"))
  redbar.position = [251, 330]
  Stage << redbar

  greenbar = Bitmap.new(Texture.new("green-bar.png"))
  greenbar.position = [251, 360]
  Stage << greenbar

  bluebar = Bitmap.new(Texture.new("blue-bar.png"))
  bluebar.position = [251, 390]
  Stage << bluebar

  reddot = Bitmap.new(Texture.new("red-dot.png"))
  reddot.y = 322
  Stage << reddot

  greendot = Bitmap.new(Texture.new("green-dot.png"))
  greendot.y = 352
  Stage << greendot

  bluedot = Bitmap.new(Texture.new("blue-dot.png"))
  bluedot.y = 382
  Stage << bluedot

  # frame counter
  frame = 0

  Stage.on :enter_frame do |dt|
    # animate r,g,b multipliers of color transform
    r = (Math::sin(frame * 0.5 + 0.3) + 1) / 2
    g = (Math::sin(frame * 0.8 + 0.2) + 1) / 2
    b = (Math::sin(frame * 1.3 + 0.6) + 1) / 2
    frame += dt

    # set color transform
    bitmap.color = [r, g, b, 1]

    # update the positions of dots
    reddot.x = 250 + r * 280
    greendot.x = 250 + g * 280
    bluedot.x = 250 + b * 280
  end

end
