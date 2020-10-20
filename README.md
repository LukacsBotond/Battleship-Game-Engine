<h2>Battleship-Game-Engine</h2>

Command line based Battleship game currently in development.

<h3>Features</h3>

  - [x] Set the map size as you like
  - [x] Set the usual ships (**Aircraft carrier**, **Destroyer**, **Cruiser**, **Battleship**) where you want them, by setting the starting coordinate and the ship direction
  - [ ] A main menu where setting the map size and the ships are possible
  - [ ] Tutorial option in the main menu
  - [ ] AI or Multiplayer option
  - [ ] Setting multiple ships from the same type so bigger maps are playable
  - [ ] After setting the map size give recomendation of the number of ships to be placed so the map won't be too empty or too full
  - [ ] A main loop which goes till someone wins or surrender, host start first
  - [ ] End screen after someone wins, dispalying hit ratio
  
  - The Host (or player in vs AI) gives the map size and the number of ships from each type and the other side have obey that
  - The players don't get both map, they can only send the coordinates where to shoot and the other side sends back if it missed, hit
  - AI sets the ships randomly
  - AI difficulties: Carpet bomber, random, random but smartter (it checks if the last shot has hit and try to go in the same dirrection if possible and avoid hitting places where it is not possible to be a ship there, like an 1-1 hole covered with shots)
  
