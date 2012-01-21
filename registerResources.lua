-- All media resources of the game are registered here.
-- They will be accessed from their alias in the C++ code.
-- Syntax: list:addItem(type, path, alias);
function registerResources(list)
	dir = "resources/";

	T = "IMAGE";
	list:addItem(T, dir.."main_menu_background.png", "main");
	list:addItem(T, dir.."target.png", "target");
	list:addItem(T, dir.."shot.png", "shot");
	list:addItem(T, dir.."cursor.png", "cursor");
	list:addItem(T, dir.."grenade.png", "grenade");
	list:addItem(T, dir.."item_ballshooter.png", "item_ballshooter");
	list:addItem(T, dir.."item_grenade.png", "item_grenade");
	list:addItem(T, dir.."clash.png", "clash");
	
	T = "SOUND";
	list:addItem(T, dir.."triangle.ogg", "test");
	list:addItem(T, dir.."spawn.ogg", "spawn");
	list:addItem(T, dir.."shockfire.ogg", "shoot");
	list:addItem(T, dir.."ricochet.ogg", "ricochet");
	list:addItem(T, dir.."explosion.ogg", "explosion");
	list:addItem(T, dir.."explosion2.ogg", "explosion2");
	list:addItem(T, dir.."guiOpen.ogg", "guiOpen");
	list:addItem(T, dir.."guiClose.ogg", "guiClose");
	list:addItem(T, dir.."guiSelect.ogg", "guiSelect");
	list:addItem(T, dir.."guiPress.ogg", "guiPress");
	list:addItem(T, dir.."guiError.ogg", "guiError");
	list:addItem(T, dir.."guiInfo.ogg", "guiInfo");
	list:addItem(T, dir.."editorPlace.ogg", "editorPlace");
	list:addItem(T, dir.."launch.ogg", "launch");
	list:addItem(T, dir.."item_pick.ogg", "item_pick");
	
	T = "FONT";
	list:addItem(T, dir.."consola.ttf", "monofont");

	T = "POSTFX";
	list:addItem(T, dir.."colorize.sfx", "colorize");
	list:addItem(T, dir.."wave.sfx", "wave");
end
