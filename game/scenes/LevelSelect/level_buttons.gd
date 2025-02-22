extends VBoxContainer

var levels: Array = []
@export var levels_path: String

func is_level_name(filename: String) -> bool:
	if filename.get_slice("_", 0) != "level":
		print("Filename at current index, " + filename + " not a level")
		return false
	else:
		print(filename + " identified as a level")
		return true

func add_all_buttons() -> void:
	var levels_dir: DirAccess = DirAccess.open(levels_path)
	if levels_dir:
		levels_dir.list_dir_begin()
		var filename = levels_dir.get_next()
		# loopthrough the filenames in levels_path (directories excluded)
		var i: int = 1;
		while filename != "" and not levels_dir.current_is_dir():
			
			if is_level_name(filename):
				print("Adding button")
				
				var new_button = Button.new()
				new_button.text = "Level " + str(i);
				add_child(new_button)
				
				i += 1
			else:
				print("Skipping")

			filename = levels_dir.get_next()
	else:
		print("Openning directory " + levels_path + " failed")
		return

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	add_all_buttons()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
