module Game
  include RubyAction

  cartoon = TTFont.new "cartoon.ttf", 60
  almendra = TTFont.new "almendra.ttf", 60
  eroded = TTFont.new "eroded.ttf", 60

  text = TextField.new cartoon, "Cartoon Blocks Christmas"
  text.anchor = [0.5, 0.5]
  text.position = [100, 100]
  text.color = [1, 0, 0, 1]

  Stage << text

  text = TextField.new almendra, "Almendra"
  text.anchor = [0, 1]
  text.position = [100, 250]
  text.color = [0.5, 1, 0.5, 1]

  Stage << text

  text = TextField.new eroded, "Sounds Eroded"
  text.anchor = [0.5, 0.5]
  text.position = [100, 400]
  text.color = [0.5, 0.3, 1, 1]

  Stage << text

end
