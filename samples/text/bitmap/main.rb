module Game
  include RubyAction

  cartoon = Font.new "cartoon.txt", "cartoon.png"
  almendra = Font.new "almendra.txt", "almendra.png"
  eroded = Font.new "eroded.txt", "eroded.png"

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
