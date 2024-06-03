all_helps.versions = {}
all_helps.versions = {

  entries = {
  {
    keywords = {"version", "version note", "version notes", "versions"},
    htype = "catagory",
    level = -1,
    text = function ()
     send("&WHelp files catagorized as 'version'&D")
     send_nocr("&Y")
     hyphens()
     txt = "&W" .. get_catagory_list ("version") .. "&Y"
     send(txt)
   end,
  },
  {
    keywords = {"VERSION2.1.0"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.1.0
&R* &YAdded dreaming messages.
&w- &WWhen mortals sleep they will occasionally see a random dream message.
&R* &YAltered exp tnl calculations.
&R* &YRemoved several flags that would show up on immortals in
&Y  a 'who' listing.
&R* &YChanged 'Drazuk' to 'Darwin' for sacrifice message.
&R* &YChanged 'Drazuk' to 'Medea' for level gain message.
&R* &YEdited the way flags are displayed on mobs. Mobs with no flags are
&Y  no longer indented.
&R* &YModified OUTCAST so that level is not a factor.
&w- &WThis previously would not allow a leader that was lower level to
&W  OUTCAST another that was of a higher level. Anyone that is granted
&W  the OUTCAST command may OUTCAST anyone else in the same following.&D
]],
    see_also = {"outcast"},
  },
  {
    keywords = { "VERSION2.1.1" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.1.1
&R* &Y'sac all' implemented.
&w- &W'all' can now be used as an argument for the SACRIFICE command. This
&W  will destroy any item on the ground that the player is allowed to pick
&W  up or sacrifice individually. The output is a single line and the player
&W  is rewarded a single gold coin for each item sacrificed.
&R* &Yno_junk flag added to quest bags.
&w- &WThis is to prevent players from accidentally junking their questbag
&W  that contained all their quest eq. To get rid of bags they will have
&W  to be dropped and sacrificed.
&R* &YAvatars' mana should no longer be set to 0 when they die. Instead,
&Y  they will have just as much mana as they had when they died.
&R* &YAutosplit gold does not get split with mobs.&D
]],
    see_also = {"sacrifice"},
  },
  {
    keywords = { "VERSION2.2.0"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.0
&R* &YCharacters may now be created with names containing one(1) space
&Y  and one(1) apostrophy.
&w- &WNames are limited to a total of 25 characters in length.&D]],
  },
  {
    keywords = { "VERSION2.2.1"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.1
&R* &YSlight alterations in the display of some flags.
&R* &YAdded TNL to SCORE.
&R* &YMoved "Gold" up one line in the SCORE so that I could group XP
&Y  and TNL together.
&R* &YAdded permanent stats to MSTAT output.
&R* &YAdded word replacement for number to position in MSTAT.
&R* &YAdded EXP and TNL to MSTAT output.
&R* &YAdded Practices to MSTAT output.
&R* &YReduced wait time for TRANCE.&D]],
  },
  {
    keywords = { "VERSION2.2.2"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.2
&R* &YChanged "You receive x experience points" line to show "point"
&Y  when only 1 exp is gained.
&R* &YPCRENAME now renames the owner on quest equipment.
&w- &WThis was done to prevent quest eq from falling off of a character
&W  that was being renamed.
&R* &YADVANCETIER command no longer causes the character's practices to
&Y  be set to 20.
&w- &WIf the player has less than 20 practices upon advancing to the next
&W  tier, they are set to 20 practices, otherwise they keep the same amount
&W  of practices they originally had.
&R* &YAllowed mortals to use %c, %n and %T in prompts.
&Y  for meanings.
&R* &YUpdated help files for PROMPT, IMMPROMPT and PCRENAME.&D]],
     see_also = {"pcrename", "advancetier", "prompt", "immprompt"},
  },
  {
    keywords = { "VERSION2.2.3" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.3
&R* &YGRANTSIGHT reworked. Immortals can grantsight any player. See HELP
&Y  GRANTSIGHT for details.
&R* &YUpdated helpfile for GRANTSIGHT.&D
]],
     see_also = {"grantsight"},
  },
  {

    keywords = { "VERSION2.2.4" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.4
&R* &YFixed some messages that did not properly end in a CR/LF sequence.
&w- &WThese were messages that were not adding a blank line before the
&W  player's prompt as it should have been doing.&D
]],
  },
  {

    keywords = { "VERSION2.2.5" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.5
&R* &YFixed an issue with color codes in item short descriptions messing
&Y  up the color of the output for the IDENTIFY spell and LOOK/EXAMINE
&Y  <item> command.
&R* &YAdded key words section to IDENTIFY and LOOK/EXAMINE output.
&w- &WThe IDENTIFY output had been altered to display the item short
&W  description instead of the item keywords. Instead of changing it
&W  back to the way it was originally, I opted to add in an additional
&W  line which contains all the keywords for the item being identified.
&W  This can been seen when the item is identified or when the item is
&W  examined.&D
]],
  },
  {

    keywords = { "VERSION2.2.6" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.6
&R* &YChanged charmies code to look at caster's level instead of other
&Y  stat that could constantly be changing.
&R* &YChanged the order of spells payers needed to see magic levels on items.
&w- &WThe different magic levels (Faint - Godlike) can now be able to be
&W  seen with one or more of the detect spells.
&R* &YMobs cannot see magic flags.
&w- &WNo reason for this, really.&D
]],
  },
  {

    keywords = { "VERSION2.2.7" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.7
&R* &YCoded in a way to create endless drink containers.
&w- &WExamining a drink container that is set to endless will give a
&W  message stating that it appears bottomless.
&R* &YRemoved some safeguards that prevented immortals from casting certain
&Y  spells on mortals due to certain restrictions.
&w- &WThey were causing problems in testing things on the test port.
&R* &YReduced lag time for ORDER command.
&R* &YMob corpse weight is now determined by the mob's level.
&w- &WThis was done to prepare for future code.&D
&R* &YUpdated information in HELP ITEMVALUES.
&R* &YAdded help file entry for HELP DARWIN.
&w- &WThis contains information on how to contact Darwin.
&R* &YQuest items are now automatically removed from questbags upon
&Y  player death.
&w- &WThis is to prevent the loss of quest items through a "quest bag bug"
&W  that no one bothered to mention to me.
&R* &YInstalled a personal study for myself into the Limbo area.
&R* &YCreated a new mob spec: spec_sexist.
&w- &WIf set on a mob, it will attack players of the opposite sex. Designed
&W  with Amazons in mind.&D
]],
     see_also = {"itemvalues", "darwin"},
  },
  {

    keywords = { "VERSION2.2.8" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.8
&R* &YAdded %w option to prompts.
&w- &WThis will display a &Rx&W if the player has any kind of lag associated
&W  with a skill, spell or command, or will display a &Go&W otherwise.
&R* &YUpdated help file entry for HELP PROMPT.&D
]],
     see_also = {"prompt"},
  },
  {

    keywords = { "VERSION2.2.9" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.9
&R* &YRemoved incorrect reference to E.S.T. in TIME output.
&R* &YAdded version number to TIME command output.
&w- &WPlayers can now type TIME to check what the version of HoG is running.&D
]],
  },
  {

    keywords = { "VERSION2.2.10" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.10
&R* &YIncreased the chance randoms have of popping on mobs.
&w- &WThis increase will likely cause a lot of more powerful random items
&W  to pop. There is also a higher chance of powerful artifact magic items
&W  popping, however, they are not without penalty. See below.
&R* &YAdded random chance of deathrot for high-level randoms.
&w- &WRandom artifact items that pop with a (Powerful magic) level or higher
&W  will have a random chance of having deathrot. These items have a lesser
&W  chance of being destroyed upon player death than those items with
&W  deathrot created by conjurers.
&R* &YAll shops should now never close.
&w- &WI had too many complaints about shops closing in the middle of buying or
&W  selling items. This change renders shop open and close times in area files
&W  obsolete.
&R* &YSeveral help files relating to the legendary skills have been added.
]],
     see_also = {"legendary"},
  },
  {

    keywords = { "VERSION2.2.11" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.2.11
&R* &YCoded a new way of checking for a skill on a player.
&w- &WThe skill still does not show up in the practice list, but the player
&W  is able to use the skill.
&R* &YAdded a timer to items that fall to the ground.
&w- &WThis timer gives an item aproximately 30 minutes to exist on the
&W  ground. After that time has expired the item will be destroyed. I have
&W  also changed the default "<item> mysteriously vanishes" phrase to
&W  something more unique to this realm.&D
]],
  },
  {

    keywords = { "VERSION2.3.0" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.0
&R* &YFixed area economies.
&w- &WArea economies will now be saved when they are updated. They will also
&W  be reloaded upon mud bootup. Upon loading, the area economy gains interest
&W  at a rate of 15%.
&R* &YShopkeepers recieve no gold when they repop.
&R* &YShopkeeper inventories purge upon death.
&R* &YShopkeepers will now keep some items sold to them to be resold.
&w- &WShopkeepers will keep random item that are sold to them. These items
&W  will then be listed with the shopkeeper's other items.
&R* &YMade a change to VENTRILOQUATE output.
&w- &WThis makes the output from VENTRILOQUATE obviously different from
&W  normal conversation text.
&R* &YAdded in an automatic taxing system.
&w- &WPlayers will now be taxed 5% of the amount of gold that they recieve.
&W  The gold collected from this tax goes directly to the economy of the area
&W  they are in.
&R* &YPrevent steal from working on shopkeepers.
&w- &WThis prevents any loophole that might have been created due to the above
&W  changes to the economy and shopkeepers.&D
]],
  },
  {

    keywords = { "VERSION2.3.1" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.1
&R* &YRemoved aquabreath from popping on random items.
&w- &WThis was causing a crash.&D
]],
  },
  {

    keywords = { "VERSION2.3.2" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.2
&R* &YAdded check to ENCHANT WEAPON to accept artweapon as an acceptible spell
&Y  target.
&w- &WNon-magical artweapons can now be enchanted with the ENCHANT WEAPON
&W  spell.
&R* &YArtweapons that are enchanted will be given an enchant bonus.
&w- &WThis gives a small bonus to an enchantable artweapon.
&R* &YRemoved ENERGY DRAIN's ability to give the caster drained mana.
&w- &WThis was done to balance out the spells. ENERGY DRAIN was being used in
&W  such a way that a druid could exp contuously without the need to stop and
&W  regenerate lost stats such as hp, mana and moves. This was an unfair
&W  advantage in regards to other classes.
&R* &YIncreased the amount of exp gained from using ENERGY DRAIN.
&w- &WThis is compensation for the no mana return.
&R* &YAdded check to ENCHANT ARMOR to accept artarmor as an acceptible spell
&Y  target.
&w- &WNon-magical artarmors can now be enchanted using the ENCHANT ARMOR
&W  spell.
&R* &YArtarmor that is enchanted will be given an enchant bonus.
&w- &WThis gives a small bonus to an enchantable artarmor.
&R* &YFixed a typo in the TELESCAPE output.&D
]],
     see_also = {"enchant weapon", "energy drain", "enchant armor", "telescape"},
  },
  {

    keywords = { "VERSION2.3.3" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.3
&R* &YChanged the way code checks for shopkeepers.&D
]],
  },
  {

    keywords = { "VERSION2.3.4" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.4
&R* &YOptimized the way AUTOGOLD works.
&w- &WCharacters will no longer try to get gold from a corpse if it contains
&W  no gold to begin with. This will prevent the line "You see nothing like
&W  that in the corpse." from appearing when the corpse has no gold and the
&W  player has AUTOGOLD turned on.
&R* &YFixed a typo in the code that produced duplicate lines when splitting
&Y  gold.
&R* &YNODROP weapons can no longer be disarmed.
&R* &YDISARM skill should now have a better chance of succeeding.
&R* &YRoom info is now displayed in room for immortals.
&w- &WImmortals should now see room info in the rooms such as area name, area
&W  file name, room vnum, room flags, exits, exit vnums, exit key vnum and
&W  sector type.
&R* &YImmortals can now walk through closed doors.
&R* &YReplaced mana spell in spec_cast_adept with cure critical.
&R* &YMade some adjustments to a couple spells.
&R* &YAdded SEEDAM to config settings.
]],
     see_also = {"config"},
  },
  {

    keywords = { "VERSION2.3.5" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.5
&R* &YCreated new spell: ENCHANT TREASURE
&w- &WThis spell allows the caster to enchant a "treasure" or "arttreasure"
&W  type item. The effects are +spell dam and +mana. This spell is usable on
&W  magical or non-magical items but not enchanted items. This spell is
&W  currently not assigned to any class.
&R* &YFixed the problem with PKillers getting the KILLER flag when their
&Y  victim is within range.
&R* &YRemoved tax from players recieving gold from other players.
&R* &YAutomatic reboots will now wait seven(7) days to reboot.
&R* &YCreated FCHARMIE command for implementors.
&w- &WThis command will set a mob or player to be the charmie of another mob
&W  or player and allows the immortal to set the charm duration.
&R* &YRecreated the SKIN skill.
&w- &WCurrently unavailable to mortals. This is being set up for use in the
&W  future.
&R* &YAltered OINVOKE so that the third paramter is quantity
&w- &WImmortals with this command can now create multiples of an invoked item.
]],
     see_also = {"enchant treasure", "fcharmie", "skin", "oinvoke"},
  },
  {

    keywords = { "VERSION2.3.6" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.6
&R* &YCharacter creation process changed.
&w- &WPlayers will now choose RACE before choosing CLASS. Class selection will
&W  be limited to available classes for the chosen race.
&R* &YReduced spell lag for many spells.
&R* &YFixed several instances of incorrect calculations of tiered levels.
&w- &WThis fixes damage cap, spell damage cap, ability to see spell rounds and
&W  affects in SCORE as well as the AFFECTED command.
&R* &YRemoved random chance randoms will have DEATHROT.
&R* &YRemoved, temporarily, the chance items with DEATHROT will be destroyed
&Y  upon death.
&R* &YMore changes to the SKIN skill.
&R* &YPrevent characters under level 4 and tiered characters from becoming
&Y  thirsty or hungry.
&w- &WFrom the looks of it, this was intended beforehand, but it only
&W  prevented the hunger/thirst messages from being displayed.
&R* &YCreated new command to reset economy values that become too large due to
&Y  numerous reboots, hotboots, and/or crashes.
]],
     see_also = {"skin", "reconomy"},
  },
  {

    keywords = { "VERSION2.3.7" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.7
&R* &YAdded a check in ENCHANT ARMOR, ENCHANT TREASURE and ENCHANT WEAPON to
&Y  disallow enchanting an item while it is being worn.
&R* &YSKIN nearly completed.
&w- &WSKIN works as intended. I still need to create a new skin object in an
&W  area file for the skill to use. Other alterations will be required before
&W  mortals are allowed to use this skill.
&R* &YAdded check in FORCE command to allow implementors to force other
&Y  implementors. (By request)
&R* &YPlayers with should now be able to drink even with a full stomach.
&w- &WPreviously, drinking caused a character's FULL and THIRST to increase
&W  and would not allow a character to drink if FULL was set at maximum. This
&W  change allows a character to drink even if FULL is at maximum but will
&W  prevent a player from drinking if THISRT is at maximum.
&R* &YFixed class selection for character creation.
&w- &WA mishap caused the selection of classes to actually be the disallowed
&W  classes for that class causing races such as human to actually list no
&W  classes at all.
&R* &YLow level tiered characters can now see numeric value of armor in score.
&R* &YAdded "Eff" to tiered characters SCORE to show effectively what level
&Y  they are.
&w- &WThis will show in the tiered character's score next to the class name as
&W  "Eff: #"
&R* &YBasic outline of two new spells.&D
]],
     see_also = {"enchant armor", "enchant treasure", "enchant weapon", "skin" },
  },
  {

    keywords = { "VERSION2.3.8" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.8
&R* &YFixed a bug with the undertaker's corpse retrieval code.
&R* &YMoved ENCHANT ARMOR to cleric/bishop.
&R* &YGave ENCHANT TREASURE to mage/archmagi.
&R* &YItems with DEATHROT should not purge upon death. For real this time!
&R* &YAdded randomized data stuffs to appropriate room types.
&w- &WThis is for future development.
&R* &YQuaffing potions does not cause the character's stomach to become full.
&R* &YPrevent immortals from doing Mob Masteries.
&R* &YFixed a bug in the GROUP command that was causing crashes.
&R* &YAdded 'height' and 'weight' options to MSET.
&R* &YAdded a check for justified attacks.
&w- &WIf a player is attacked or stolen from by someone not in their PK range
&W  they will now be able to attack them without being flagged a killer.&D
]],
     see_also = {"enchant armor", "enchant treasure", "mset" },
  },
  {

    keywords = { "VERSION2.3.9" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.9
&R* &YAdded a way to list the item effects from a shoppie.
&w- &WA new column of numbers has been added to the output from a shop's
&W  LIST command. These numbers represent the number of the item in the shop's
&W  inventory. You can then "LIST #" to see the values of that item.
&R* &YPlayers can now "DISMISS ALL" to remove all charmies from their group.
&w- &WPlayers with multiple charmies can DISMISS ALL to release all their
&W  charmies from their control.
&R* &YPlayers can now choose a more difficult mobmastery.
&w- &WThis can be done by specifying <mobm start expert>. Be warned, the
&W  target mob will become enhanced by being chosen as the target. You may
&W  not choose an expert mobmastery until you have reached 400 regular
&W  mobmasteries.&D
]],
     see_also = {"dismiss", "mobmastery" },
  },
  {

    keywords = { "VERSION2.3.10" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.10
&R* &YReduced overall lag and tick time.
&R* &YFixed some typos.
&R* &YFixed a bug that caused AC to become way off.
&R* &YAdded 'acworn' option to MSET command.
&R* &YAdded a few more checks to reset mobs from expert mobmastery failure
&Y  or quit.
&R* &YFixed a bug with worn items being listed in shops.
&R* &YAdded removal of stay_area and sentinel specs from expert mobm targets.
&R* &YAll shoppies will now buy and sell components.
&R* &YShoppies will not buy more than one of the same item.
&w- &WShoppies will not buy more than one of an item. This affects everything
&W  sold to shoppies. For example, if a shoppie already has an item that is a
&W  "shirt" it will not buy another item that is a "shirt" If a shoppie has a
&W  boiled leather shirt, it will not buy a hard leather shirt.
&R* &YFixed a bug in the character creation process that prevented some races
&Y  from being selectable.
&R* &YRemoved checks for some portal spells so that they will succeed more
&Y  often.
&R* &YAuto-assisting combat should be noticed in the first round of combat.
&R* &YRemoved automatic WAR message when someone is attacked.
&R* &YAdded names to randomly generated items in certain room types.
&w- &WThese are visible only with the immortal RSTAT command.
&R* &YAdded drowning messages.&D
]],
     see_also = {"mset", "rstat"},
  },
  {

    keywords = { "VERSION2.3.11" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.3.11
&R* &YRemoved fight limit.
&R* &YFixed a bug with the undertaker creating duplicate corpses.
&R* &YMade a change to RECONOMY command.
&R* &YNew skills: GATHER, IGNITE, SKIN, MINE, DRY
&w- &WGATHER - This skill obtainable to anyone at any level allows the
&W  character to gather woods from forested areas.
&w- &WIGNITE - This skill obtainable to anyone at any level allows the
&W  character to ignite combustables to start a fire.
&w- &WSKIN - This skill obtainable to anyone at any level allows the
&W  character to skin the corpses of slain mobs.
&w- &WMINE - This skill obtainable to anyone at any level allows the
&W  character to mine for metals and gems in mountainous and undergound areas.
&w- &WDRY - This skill obtainable to anyone at any level allows the
&W  character to dry a previously obtained skin to create a hide.
&C  The new skills are not available to mortals as of yet. More skills are
&C  needed before they will be worth using.
&R* &YNew command: STOKE
&w- &WStoke allows the player to add more combustables to a fire which
&W  increases the fire's temperature. Use "examine ignite_fire" to check the
&W  fire's temperature.
&R* &YThe "note" item is now no_locate. This is for quest purposes.
&R* &YFixed the error with WEAPONSMITH DEVOUR which was adding the wrong spell
&Y  to weapons. (Although I heard that the bears were cute.)
&R* &YINVASION now allows immortals to specify an amount of glory to be
&Y  awarded for killing the invader.
&R* &YAdded a check in MURDER to prevent combat in safe rooms.
&R* &YPlayers should now see all skills and spells that they have access to
&Y  in their practice list. Skills not awarded by classes are still not
&Y  able to be practiced.&D
]],
     see_also = {"reconomy", "invasion", "murder"},
  },
  {

    keywords = { "VERSION2.4.0" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.0
&R* &YAdded several failure messages to the FARSIGHT spell.
&R* &YReduced the duration of the CURSE spell.
&R* &YThe charm on DAEMONIC GUARDIAN will last until the mob's death.
&R* &YCreated spells MAGIKA ARMOR, CHANNEL, ETHEREAL CLOAK, SPIRIT SYPHON,
&Y  and MANA BURN.
&w- &WThese spells are to be used for upcoming class reworkings.
&R* &YCHARM PERSON no longer causes the charmie to become aggressive towards
&Y  the charmer when the charm fades.
&R* &YMIDAS TOUCH has been tweaked to give slightly more gold.
&w- &WThe amount of gold awarded from MIDAS TOUCH is still less than the
&W  item's value, but is more than it previously was.
&R* &YMade tweak to IMPALE command.
&R* &YAdded %L token for prompts.
&w- &WSee HELP PROMPT for details. See Darwin if still confused.
&R* &YPrompt will now auto refresh if you are in a wait state.
&w- &WThis will be most notable if you are using the %w token in your prompt.
&R* &YRemoved slight lag when moving room to room.
&R* &YFixed the infamous "ac bug" caused by etching.
&w- &WIf you have been previously etched and your ac is off, you may need it
&W  fixed one last time.
&R* &YMade some changes to player deaths regarding quest-flagged equipment.
&w- &z1) &WPlayers who die to mobs will repop with their quest eq as normal.
&z  2) &WPlayers who die to immortals will repop with an empty quest bag.
&z  3) &WPlayers who die to other players will repop with an empty quest bag.
&w- &WAt this time players cannot wear equipment that is owned by another
&W  player. It will probably be best to return quest equipment to its owner
&W  if you kill someone that has any such items.
&R* &YMade changes to DONATE and FSTORE.
&w- &WSee below.
&R* &YMade changes to donation pits and pit room mobs.
&w- &WTo prevent stock piles of stock equipment that has occured players may
&W  no longer donate or fstore any item that is not flagged as random. Mobs
&W  in pit rooms that collect items from the ground and place them in the pit
&W  will no longer pick up stock items and will drop any stock items handed
&W  to them. They will also not pick up any containers that have stock items
&W  in them and will drop any containers that have stock items in them. This
&W  change does NOT affect lockers. You can still store stock items in your
&W  lockers if you have one.
&W  &RWARNING: This is probably going to cause some headaches at first until
&R  all the items in following pits are marked as randoms as the older randoms
&R  had no such flag on them.
&R* &YCreated immortal SETRANDOM command.
&w- &WThis command is used to set the random flag on an item so that it may be
&W  stored in a donation container.
&R* &YUpdated the following help files: PROMPT, DEATH, IMPALE, FSTORE, DONATE
&R* &YCreated the following help files: 'QUEST EQUIPMENT', SETRANDOM&D
]],
     see_also = {"impale", "prompt", "donate", "fstore", "setrandom", "death", "quest equipment" },
  },
  {

    keywords = { "VERSION2.4.1" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.1
&R* &YAdded option AUTOUPDATE to config settings.
&R* &YStock items will pop with a cost value of 0.
&R* &YCreated spells DISRUPT GRAVITY, DISRUPT PHYSICS, KINETIC SHIELD,
&Y  ETHEREAL STORM, SPELL SURGE, MAGIKA RAGE, DIVINE WINGS, DAEMONIC GRACE,
&Y  SPIRIT GUIDE, DAEMONIC FLAME, DARKNESS BINDS.
&w- &WSee individual helps. These spells are to be used for upcoming class
&W  reworkings.
&R* &YImpaled corpses can be sacrificed.
&R* &YPatched a loophole in donation pit code.
&R* &YAdded PERSONAL LOCKERS.
&R* &YAdded timestamp %t token for prompts.
&R* &YThe following skills and spells created by Cahel: POLTERGIEST,
&Y  SWORD SERENADE, WRIST SLASH, WHISPER BLADE, BLADE DANCER, LEFT HAND,
&Y  CAPOEIRA, HIGH GUARD, TELEGRAPH, SOUTH PAW, LOW GUARD, LIQUID SWORD,
&Y  SHELL DEFENSE, CLINCH, DEFIANCE, CELESTIAL GUARDIAN, SPIRIT CHARGER,
&Y  ANSWERED PRAYERS, DAEMONIC SCYTHE, DIVINE AVATAR, DESPERATE PLEA,
&Y  HEAVEN AND HELL, CATNAP, INVIGORATE, NIRVANA, GHOST STRIKE, GARROTE,
&Y  FISHHOOK, GNAW, STREET BRAWLER, FIRE FIST, CRASHING WAVE, SHOCK STRIKE,
&Y  ICE PALM, and PRESSURE POINT.
&w- &WSee individual helps. These spells are to be used for upcoming class
&W  reworkings.
&R* &YAdded data to system settings to track number of new characters.
&R* &YAdded an ID number to player files to uniquely identify each new
&Y  character.
&R* &YMSTAT now shows character ID# where Vnum was previously placed.
&R* &YCorrected spell GOLEM WEAPON.
&R* &YDestroying/deleting a character also deletes their locker file if
&Y  they have one.&D
]],
     see_also = {"config", "personal lockers", "prompt" },
  },
  {

    keywords = { "VERSION2.4.1A" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.1a
&R* &YFixed an oopsie.&D
]],
  },
  {

    keywords = { "VERSION2.4.1B" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.1b
&R* &YFixed another oops.&D
]],
  },
  {

    keywords = { "VERSION2.4.2" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.2
&R* &YAPPLY_JUMP, APPLY_WAIT coded.
&R* &YAdded APPLY_JUMP and APPLY_WAIT to sset options.
&R* &YAdded individual class if_checks to mobprogs.
&R* &YUpdated guildmasters in Alden with new ifchecks.
&w- &WNew ifchecks allow a warrior-mage to enter either warrior guild
&W  or mage guild. It also allows tiers to enter their pre-tier guilds,
&W  such as an archmagi is able to enter mage, conjurer or druid guilds.
&R* &YAdded more options to SSET and SPELLCOMPONENTS.
&R* &YFollowing help files created or updated: SPELLCOMPONENTS, SSET,
&Y  'IFCHECK CLASS', SPELLFLAGS, DICEFORMULAS, SSET2, NON-VERBAL
&R* &YNew spells and skills: DISRUPT REALITY, MUTE, ENHANCE AURA,
&Y  ARMOR OF LEAVES, NATURES WRATH, BLADE SPIRIT, CORRUPT ARMOR,
&Y  DAEMONIC ARMOR, HIGHER CALLING, HOLY FLAME, IDOL, APOLOGIZE, BLITZKRIEG,
&Y  DIE LAUGHING, DISENGAGE, FLASH BANG, HIGH JUMP, LEFT HANDED, SOUTHPAW,
&Y  VANISH, TACTICAL RETREAT, ENHANCE AURA, ENJOYING THE GAME, RIPOSTE,
&Y  TREAGE, SERPENT KISS, SHIELD SLAM, DAEMONIC PACT, CELESTIAL TRUPMETS,
&Y  SKIRMISH LINE, ORDER RANKS, FINAL STAND, PINCER MOVEMENT, CLEANSE AURA,
&Y  TENDON STRIKE
&w- &WSee related help files.
&R* &YCreated mob Ethereal Guardian for spell DISRUPT REALITY.
&R* &YCreated spell flag NONVERBAL.
&w- &WA nonverbal spell is not uttered and can be cast even if the caster
&W  is affected by the MUTE spell.
&R* &YThe following spells are now non-verbal: ACID BREATH, FIRE BREATH,
&Y  FROST BREATH, GAS BREATH, LIGHTNING BREATH and TELEPORT.
&R* &YAdded percent-based and group members operators to dice formulas.
&w- &WThese will cause the affects or duration of a spell or skill to be based
&W  on the player's current health, mana or moves percentages or based on
&W  number of members in the player's group, including or excluding NPCs.
&W  See HELP DICEFORMULAS.
&R* &YMoved message from greeting screen telling names can include a space and
&Y  apostrophe to new character name screen.
&R* &YMobs summoned from spells DEMONIC BEAST, DAEMON GUARDIAN and SUMMON
&Y  GOLEM will now be automatically grouped with the summoner.
&R* &YSpell DEMONIC BEAST tweaked.
&w- &WDemons summoned with this spell should be more useful and last longer.
]],
     see_also = {"sset2", "ifcheck class", "nonverbal", "diceformulas" },
  },
  {

    keywords = { "VERSION2.4.3" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.3
&R* &YModified get_exp_base function in anticipation for changes to tiers.
&Y  (has no effect on gameplay or exp tnl yet)
&R* &YRemoved need for questbag.
&w- &WAll quest items will repop on you when you die, mob or pk.
&R* &YETHEREAL GUARDIANS will vanish once their charm expires.
&w- &WThese are mobs for a new archmagi spell not currently available.
&R* &YCharacters under level 10 will retain their gold when they die.
&R* &YMade changes to how conjurer-enchanted equipment functions after a pk.
&R* &YFixed an issue that occured when trying to give an item to yourself.
&R* &YCharacters under level 5 can have at least 1 charmie.
&R* &YCharacters will now see &W(&znothing&W)&Y when they have an empty wear
&Y  slot. &RNote: &YThis may also show slots not available such as dual-wield.
&R* &YConjurer's are limited to enchanting randoms only.
&R* &YSeveral tweaks to the spell BOTTLE and related UNBOTTLE command.
&w- &WBottled mobs are now owner flagged to the bottler. Players may not
&W  unbottle a mob that does not belong to them. Bottles may be auctioned
&W  with a starting price of at least 20,000 gold. A 50% fee is charged to the
&W  seller to pay for change of ownership fees.
&R* &YBottles created from the spell BOTTLE are now of type trash.
&w- &WBottles were drink containers. Drinking from them could cause the mob to
&W  pop out of the bottle with missing or incorrect stats.
&R* &YAll conjurer ARMORSMITH and WEAPONSMITH spells have been tweaked.
&R* &YRemoved the MUD's ability to write to a bugs.txt file.
&w- &WThis file was constantly becoming corrupt, crashing the mud and further
&W  preventing the mud from successfully rebooting.
&R* &YHopefully fixed an odd bug where a charmed mob's charm expired and it
&Y  would cause the player to seemingly fight themselves.
&R* &YAdded the 'random' flag to severed body parts so they can be fstored and
&Y  donated as randoms.
&R* &YFixed ENHANCED DAMAGE that was incorrectly calculating a tier's level.
&R* &YFixed ENHANCED HIT that was incorrectly calculating a tier's level.
&R* &YRemoved an annoyance associated with 'get all' and player corpses.
&R* &YCreated immortal command OGET.
]],
     see_also = {"conjurers equipment", "oget" },
  },
  {

    keywords = { "VERSION2.4.4" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.4
&R* &YLinkdead immortals should be immediatly logged off.
&R* &YTweak to ENCHANT TREASURE.
&R* &YTweak OWHERE to show object id.
&R* &YSafety tweaks to OGET.
&R* &YSteamlined the ADVANCETIER code.
&R* &YMade ADVANCETIER compatable with future tier setup.
&w- &WCharacters using the ADVANCETIER command will now notice they will have
&W  two different classes shown in their score. Their class will be the tier
&W  class and their dualclass will be their original class.
&R* &YTweaked can_see so any level tier can see wizinvis 50 immortals.
&R* &YRacial stats override class stats as far as which one is higher.
&w- &WIf a character's racial stat's max is higher than their class stat's max
&W  thier stat's max will be the racial max. For example: A Minotaur's max
&W  strength is 21 and a mage's max strength is 20. If the minotaur was a
&W  mage, its strength would max at 21 since the racial stat was higher.
&R* &YTweak class/level output in WHO command to show full class name of
&Y  tiered characters.
&R* &YCosmetic alteration to info message from someone becoming tiered.&D
]],
     see_also = {"owhere", "oget", "advancetier" },
  },
  {

    keywords = { "VERSION2.4.5" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.5
&R* &YAdded check so that stat max's can't exceed 25.
&R* &YAdded check for locker room flag in "locker openold" command.&D
]],
     see_also = {"locker"},
  },
  {

    keywords = { "VERSION2.4.6" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.6
&R* &Y"locker close" removes timer from items before they get saved.
&w- &WSome of you may have seen or heard about items in the old lockers
&W  being collected by Drazuk. That was due to the ground rot. When the
&W  lockers were closed, the items were saved with the ground rot timer
&W  still on them and were not reset when the locker was re-opened. This
&W  fixes that issue.
&R* &YAdded recursive check for "bags inside bags inside bags etc." for
&Y  donation commands.
&w- &WThis will prevent bags within bags (etc.) that contain stock items from
&W  being donated, fstored or put inside donation pits.
&P  FOLLOWING LEVEL IMMORTALS: Please take the time to check containers within
&P  your pits and make sure they are marked random (SETRANDOM) as needed.
&R* &YENCHANT ARMOR/TREASURE/WEAPON tweaks.
&w- &WThese tweaks do not alter any of the affects of the spells and should
&W  not be noticed.
&R* &YNew tier spell PIERCE SHADOWS created.&D
]],
  },
  {

    keywords = { "VERSION2.4.7" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.7
&R* &YCreated SF_NOCLASS flag for skills.
&w- &WThis flag allows setting certain skills and spells as a non-class
&W  specific skill, such as legendary skills.
&R* &YIncreased the chance of practices being rewarded for completing aquests.
&R* &YAdded a new "keyword" option to QPBUY.
&w- &WThis option will allow a character to buy a specialized keyword for an
&W  item using glory points. See HELP QPBUY.
&R* &YForced a strict +/-10 level restriction on STEAL between players.
&w- &WThis i&Rs&W the resu&Rl&Wt of a player ab&Ru&Wsing it by st&Re&Waling
&W  from players out of his range.
]],
     see_also = {"qpbuy"},
  },
  {

    keywords = { "VERSION2.4.8" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.8
&R* &YFixed a loophole in the EMPTY command.
&R* &YReduced prices for Kallista's services.
&w- &WMoney used for Kallista's services are added to Alden's economy.
&R* &YCoded new skill SALT WOUNDS.
&R* &YPossibly fixed an issue with the anti-tanking code.
&R* &YAdded HELP EQSWAPPING&D
]],
     see_also = {"empty", "eqswapping" },
  },
  {

    keywords = { "VERSION2.4.9" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.9
&R* &YChanged mobprog ifcheck 'isthief' to 'isathief' to remove conflict
&Y  with class check 'isthief' for guildmasters.
&R* &YRemoved restriction for AUTOUPDATE config setting from fighting.
&w- &WFurther testing proved that the fight prompt was not being autoupdated
&W  as often as it should have been.
&R* &YChanged spell ENCHANT TREASURE to ENHANCE TREASURE.
&R* &YMade tweaks to ENHANCE TREASURE.
&R* &YCreated spells ENCHANT TREASURE, ENHANCE ARMOR and ENHANCE WEAPON.
&R* &YMade tweaks to ENCHANT ARMOR and ENCHANT WEAPON.
&w- &WEnhance spells are designed to benefit caster classes. These spells will
&W  be given to mages. Enchant spells are designed to benefit combat oriented
&W  classes and will be given to clerics. See related help files.
&R* &YAdded three new act flags for mobs: Aggressive_low, Aggressive_mid and
&Y  Aggressive_high.
&w- &WAggressive_low: Mobs with this flag will aggressively attack players
&W  level 15 and below only.
&w- &WAggressive_mid: Mobs with this flag will aggressively attack players
&W  level 16 and above only.
&w- &WAggressive_high: Mobs with this flag will aggressively attack players
&W  level 30 and above only.
&R* &YObjects that are zapped from a character will stay in the character's
&Y  inventory instead of falling to the ground.
&R* &YAdded AUTOASSIST config option.
&w- &WThis option, when set, will cause the character to automatically
&W  assist group members in a fight. If not set, the character will sit
&W  idly by while their groupmates continue the fight without them.
]],
     see_also = {"config"},
  },
  {

    keywords = { "VERSION2.4.10" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.10
&R* &YAdded config ABBAFFS (abbreviated affects) option to config settings.
&w- &WThis setting when on will abbreviate spells seen on other characters
&W  into a single set of single color-coded letters. This setting is off
&W  by default. See HELP ABBAFFS for more information.
&R* &YFixed problem with invis and imp invis showing the invis flag twice.
&R* &YPlayers can now see the neutral align aura if they are affected by both
&Y  detect good and detect evil.
&R* &YCreate real random potions, pills, wands, scrolls, staves and salves.
&R* &YPlayers with CONFIG +SEEDAM will now see a numerical value of damage
&Y  delt to them by mobs.
&R* &YCharmies automatically assist in combat.&D
]],
     see_also = {"abbaffs"},
  },
  {

    keywords = { "VERSION2.4.11" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.11
&R* &YFixed at least 2 errors that were causing null spells to end up on
&Y  random magic consumables.
&R* &YAdded spell names to keywords list of magic consumable items.
&w- &WSince this change would make it extremely easy to locate specific
&W  spells on these items, they are now nolocate.
&R* &YAdded a new preset prompt 'hog1'
&w- &WTo use this preset type: prompt hog1
&R* &YAdded a new preset fprompt 'hog1'
&w- &WTo use this preset type: fprompt hog1
]],
     see_also = {"prompt", "fprompt"},
  },
  {

    keywords = { "VERSION2.4.12" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.12
&R* &YImmortals can now see any level mobinvis.
&R* &YCreated new command CONVERT.
&w- &WThis command is mainly for tiers but can be used by any player.
&R* &YAdded bonus info from a specific IDENTIFY output.
&R* &YIncreased the amount of experience gained from physical attacks.
&R* &YAdded level constraints to function is_legal_kill.
&w- &WThis fixes an issue with HITALL enabling players to attack those outside
&W  of their range. It may also fix a similar issue with some other skills.
&R* &YFixed an issue with conjurer-enchanted equipment incorrectly getting
&Y  the PK timer set on them.
&R* &YAdded 'Spirit shield' to SCORE output.
&R* &YAdded something to help players with random magic consumables.
]],
     see_also = {"convert"},
  },
  {

    keywords = { "VERSION2.4.13" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.13
&R* &YRemoved immune casting on characters for spell IDENTIFY.
&R* &YRemoved restriction that prevents AVATAR level characters from
&Y  gaining exp.
&R* &YIDENTIFY removes 'nolocate' flag from random items.
&R* &YAdded more color to IDENTIFY output.
&R* &YFixed an issue with the capitalize function messing up color codes
&Y  in items being sold in shops.
&R* &YAllow shoppies to buy more than one of the same type of item if
&Y  the item is a random.
&R* &YTweak to spell DISPEL MAGIC.
&R* &YCreated skill CRUSH. See related help file.
&R* &YTweak skill AMBUSH.
&R* &YCreated skill SHADOW VENOM. See related help file.
]],
  },
  {

    keywords = { "VERSION2.4.14" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.14
&R* &YMade tweaks to combat functions.
&w- &WFixed AC calculations. Fixed level calculations for parry check,
&W  dodge check and tumble check.
&R* &YMobs can not disarm or parry unless wielding a weapon.
&R* &YRemoved some spells from random potion/pill/salve list.
&R* &YMade a run through the random generating code to make sure items have
&Y  a value greater than 0.
&R* &YCreated skills: SNIPE, VENOM ARROW, BARBED ARROW and NUMBING ARROW.
&R* &YMade tweaks to the following spells: MIDAS TOUCH, HAND OF CHAOS,
&Y  DISRUPTION, SONIC RESONANCE, SULFUROUS SPRAY, CAUSTIC FOUNT, ASTRAL RIFT,
&Y  ACETUM PRIMUS, GALVANIC WHIP, MAGNETIC THRUST, QUANTUM SPIKE, BLACK HAND,
&Y  BLACK FIST, BLACK LIGHTNING, EARTHQUAKE, FIREBALL, IDENTIFY and TRANSPORT.
&w- &WTweaks mostly include adding spell damage or preventing area spells from
&W  hitting grouped characters and illegal targets. Other tweaks not worth
&W  mentioning.
]],
  },
  {

    keywords = { "VERSION2.4.15" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.15
&R* &YFixed some typos in the IDENTIFY spell.
&R* &YCoded in some helpful surprises for players that use, or can use,
&Y  charmed mobs.
&R* &YTweaked group exp gains.
&R* &YAdded same-room check to MISTWALK.
]],
  },
  {

    keywords = { "VERSION2.4.16" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.16
&R* &YCreated spell SUMMON SPIRIT.
&R* &YCharmed mobs can be ordered to rescue.
&R* &YCreated a "no_corpse" flag for certain mobs.
]],
  },
  {

    keywords = { "VERSION2.4.17" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.17
&R* &YFixed unbottled mobs HP/Max HP
&w- &WMobs should now have 100% hp when they are unbottled.
&R* &YFixed problem with camouflage.
&w- &WRangers should now be able to use camouflage.
&R* &YLowered interest rate for economy gain.
&R* &YAdded check for silenced flag to SAY command.
&w- &WSilenced players were still able to use the SAY channel when silenced.
&W  This fixes that issue.
&R* &YShow charm duration in GROUP output to master only.
&w- &WCharacters that have charmed mobs in their group can use the GROUP
&W  command to check the duration of the charm on their charmies. Other
&W  characters in the group will not see the charm duration if they are not
&W  the mob's master.
&R* &YAllow BUG messages to be displayed - not written to file.
&R* &YFix potential bug with FDEPOSIT.
&w- &WFDEPOSIT did not check to see if the depositor was in a clan before
&w- &Wdepositing the entered amount.
&R* &YCosmetics affected by config +abbaffs setting.
&w- &WThis change allows players using the config +abbaffs setting to see
&W  alignment auras as a single letter surrounded by parenthesis.
(E) = (Red Aura) : Evil alignment
(N) = (Grey Aura) : Neutral alignment
(G) = (Blue Aura) : Good alignment
]],
     see_also = {"fdeposit"},
  },
  {

    keywords = { "VERSION2.4.18" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.18
&R* &YIncentives to not killed one's own charmed mobs.
&w- &WAnyone that kills a mob that they have charmed will be rewarded with
&W  negative experience.
&R* &YCannot disband charmies.
&w- &WDisbanding charmies was causing some data errors.
&R* &YFix issue with characters not able to use low level scrolls.
&R* &YFix issues with eating and drinking.
&R* &YSpells HAND OF CHAOS and DISRUPTION should give some exp.
&R* &YAdded caster's name (as owner) to portal object.
&R* &YAdded flag to allow for PLANT mobs.
&R* &YDisabled all "affect-skill" affects from items and/or spells.
&w- &WThis will disable any skill bonuses applied by wearing items such as the
&W  track bonus on tracking goggles. This change may be temporary.
&R* &YMade plant corpses for mobs marked "plant" flag.
&w- &WCan now create plant mobs such as Ents.
&R* &YAdded a message to indicate dropped eq/gold from mobs with "no corpse"
&Y  flag.
&R* &YAllow jesters to use wands.
]],
  },
  {

    keywords = { "VERSION2.4.19" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.19
&R* &YFix to convert and item-skill problem.
&R* &YAllow "affect-skill" affects from items again.
&R* &YAdded safeguards to charm spells expiring.
&w- &WAdded some extra safeguards to see if they will prevent the game going
&W  into an infinite loop.
&R* &YAdded charmed info to mobs.
&w- &WCharmed mobs will return to where they came from once their charm has
&W  expired and they stop following.
&R* &YRewrote SCORE code.
&w- &WThe SCORE command would cause the mud to freeze up by causing it to go
&W  into an infinite loop. Hopefully this will fix that.
&R* &YAllow conjurers to use scrolls. < as per HELP MAGICTABLE >
&R* &YRemoved shaman ability to use staves. < as per HELP MAGICTABLE >
&w- &WThese two changes to item usage are due to the chart found in HELP
&W  MAGICTABLE. Everything is now set by that chart.
&R* &YCreated spell ALCHEMY GOLD.
&R* &YRemoved pratice gain from CONVERT command.
&w- &WSufficiant time has passed that anyone wanting to convert and regain
&W  some practices should have done so by now. This was also done to prevent
&W  any other kind of misuse or abuse.
&R* &YFix bug in SPLIT/AUTOGOLD to prevent mobs from gaining gold.
&w- &WCharmed mobs in groups of 2 players or more would inadvertedly gain
&W  gold. This fix prevents that.
]],
     see_also = {"magictable", "convert" },
  },
  {

    keywords = { "VERSION2.4.20" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.20
&R* &YCreated spell CLOUD EYES.
&R* &YAdded ASTRALBLOCK flag to invasion mobs.
&R* &YFixed issue with scroll level and allowed classes.
&R* &YRemoved immediate quit for linkdead immortals.
&R* &YFixed errors with STYLES.
&R* &YCreated skill FOOT STOMP.
&R* &YFix(?) player corpses becoming plant corpses.
&R* &YFix infinite loop with astral spells.
&R* &YFix(?) issue with colour spray adding multiple blindnesses.
&R* &YFixed typo in aquest.
&R* &YReduce wait time for quit mob master quest from 50 to 30 minutes.
]],
     see_also = {"mobmastery"},
  },
  {

    keywords = { "VERSION2.4.21" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.21
&R* &YFixed an issue with can_charm function.
&R* &YMade locate object not locate items on immortals.
&R* &YFix typos in deposit and withdraw.
&w- &WChanged deposit tax message.
&R* &YAdded skill quests (squest) and related commands.
&R* &YAdded magic quest (mquest) and related commands.
&w- &WSkill and magic quests are available from guild masters via the SQUEST
&W  or MQUEST commands. Squest are only available to a character with a
&W  fighter class (warrior, thug, thief, ranger, monk or jester) while Mquest
&W  is only available to characters with a caster class (mage, cleric, druid,
&W  conjurer, diabolist or shaman.)
&W  These quests work in the same way that Aquests work, using the REQUEST,
&W  REFUSE, COMPLETE, POINTS command options.
&W  Skill quests will reward a character with skill points while magic quests
&W  will reward a character with magic points. You will see these in your
&W  score or by using the associated POINTS command option. (SQUEST POINTS or
&W  MQUEST POINTS)
&W  A character will gain one(1) point of damage roll per every 250 skill
&W  points earned.
&W  A character will gain one(1) point of spell damage per ever 250 magic
&W  points earned.
&R* &YAdded spoint, mpoint option to MSET.
&R* &YAdded SPSET and MPSET commands.
&w- &WThese two commands work in the same way that QPSET works.
]],
     see_also = {"mquest", "squest", "mset", "spset", "mpset"},
  },
  {

    keywords = { "VERSION2.4.22" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.22
&R* &YAdded separate flags for magic/skill quests.
&R* &YFixed bugs in new squest/mquest quests.
&R* &YAdjusted wait times for squest/mquest quests.
]],
  },
  {

    keywords = { "VERSION2.4.23" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.4.23
&R* &YAdjusted wait times for squest/mquest quests.
&w- &WTimes have been increased slightly from 2 minutes to 5 minutes.
&R* &YAdjusted amount of skill/magic points needed for bonus.
&w- &WThe amount of skill or magic points needed to gain a bonus has been
&W  increased to 350.
&R* &YSeparated quest timers.
&w- &WThis allows a player to do a normal quest (AQUEST) and immediatly
&W  attempt a magic quest (MQUEST) or (SQUEST). You can still only do one
&W  quest at a time, but they are on separate timers. The "You may quest
&W  again" messages will show you when you can do another magic or skill
&W  quest. For example: This will not allow you to do a magic quest and then
&W  do another magic quest immediatly afterwards but you can do a skill quest
&W  or regular quest instead.
&R* &YPrevent limbo.are mobs from being targets of quests.
&w- &WThis includes spirits, demons, animated corpses, natures
&W  companions, etc.
&R* &YPrevent gallery.are mobs from being normal mob mastery targets.
&w- &WThese mobs were not meant to be killed by a single player. These mobs
&W  are not, however, excluded from expert mob masteries.
&R* &YAdjust dr/hr on expert mobm targets.
&w- &WHopefully make them a bit beefier.
&R* &YAdjust tick/pulse timers.
&w- &WThis may have been the cause of quest timers making players wait 10 or
&W  more minutes when the message said the wait time was much less.
&R* &YCreate custom messages for squest/mquest.
&w- &WSkill and magic quests have some unique quest messages that Joey
&W  does not say.
&R* &YAdded scorexp, scoremp, scoresp data to pc structure, save/load data.
&R* &YAdded commands for scoremp, scoresp, scorexp.
&w- &WCommands SCOREMP, SCORESP and SCOREXP now show rankings like the
&W  other SCORE- commands.
]],
     see_also = {"scoremp", "scoresp", "scorexp"},
  },
  {

    keywords = { "VERSION2.5.0" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.0
&R* &YIncreased max race so new races could be added.
&w- &WHINT! Go vote for the race names!!
&R* &YFix can_charm function.
&R* &YFix bug with spelldamage and death.
&R* &YAdded spelldam and acworn to fixchar command.
&R* &YFix in "mquest request"
&w- &WWas showing wrong time remaining.
&R* &YFix some level check errors in scribe and brew.
&R* &YPrevent renaming of PCs via mset command.
&R* &YPrevent muted mobs from casting defense spells.
&R* &YAllow shamans to use scrolls.&D
]],
  },
  {

    keywords = { "VERSION2.5.1" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.1
&R* &YAdded messages to MUTE spell.
&R* &YPrevent muted mobs from casting attack spells.
&R* &YFix typo in MQUEST REQUEST.
&R* &YAll immortals spells will now cost 15 mana.
&R* &YIncreased regen rates for mana, hp and moves.
&R* &YAdded new races: SHURI, ZEPHYR, GULRAN, AHPOCK, and JINN.
]],
     see_also = {"shuri", "zephyr", "gulran", "ahpock", "jinn"},
  },
  {

    keywords = { "VERSION2.5.2" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.2
&R* &YAdded short versions of new race names for WHO output.&D~
]],
  },
  {

    keywords = { "VERSION2.5.3" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.3
&R* &YFixed bug with spelled-up charmies.
&w- &WIt is now safe to spell-up your charmies. This will no longer cause
&W  the game to crash.&D
]],
  },
  {

    keywords = { "VERSION2.5.4" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.4
&R* &YModified WHO output.
&w- &WThis will allow all players to see any mortal currently online displayed
&W  on the WHO command output. This will not allow players to see invis,
&W  hidden or camouflaged players in rooms if they are not normally able to
&W  see such players.
&R* &YUpdated help files for SHURI, GULRAN, ZEPHYR, JINN and AHPOCK to show
&Y  exp gain percentages.
]],
     see_also = {"shuri", "gulran", "zephyr", "jinn", "ahpock"},
  },
  {

    keywords = { "VERSION2.5.5" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.5
&R* &YModified undertaker code.
]],
     see_also = {"cr"},
  },
  {

    keywords = { "VERSION2.5.6" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.6
&R* &YFix bug with WHO and GS
&R* &YFix bug with undertaker code.
&R* &YFix error with Ahpock race name not showing up in WHO output.
&R* &YAdded code to handle ENHANCED DUAL WIELD
]],
     see_also = {"enhanced dual wield"},
  },
  {

    keywords = { "VERSION2.5.8" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.8
&R* &YAdded a new greeting screen.
]],
     see_also = {"greeting4"},
  },
  {

    keywords = { "VERSION2.5.9" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.5.9
&R* &YBegan adding code to display online stats for the web site.
&R* &YFixed message with carrying too many items or too much weight.
&w- &WIt now displays the object's short description instead of its
&W  first keyword.
&R* &YAdded glory rewards for &Cwinning&Y at ACRO.
&w- &WGlory awarded will be equal to the number of votes plus the number
&W  of wins the player currently has. So, the more times you win, the more
&W  glory you can be awarded. The game requires a minimum of 3 players and
&W  you cannot vote for your own acro.
]],
     see_also = {"acro"},
  },
  {

    keywords = { "VERSION2.6.0" },
    level = -1,
    htype = "version",
    text = [[
&Cv2.6.0
&R* &YAdded Lua scripting engine to the source code with help
&Y  from Nick Gammon.
&w- &WThis allows the addition of many scriptable features such
&W  as quests, skills, commands, etc.
&R* &YAdded TASK command.
&w- &WThis is a Lua script written by Nick Gammon. See HELP TASK.
&W  The TASK system currently only has taks available for newbies
&W  in the Alden University. Other areas will get tasks as
&W  we get time to write them.
&R* &YAdded WHEREIS command.
&w- &WThis is a Lua script written by Nick Gammon with help from
&W  Ked and Indoum. ( http://www.gammon.com.au/forum/bbshowpost.php?id=7306 )
&W  Currently only the university and Alden have destinations
&W  set for the WHEREIS command. Other areas (home towns or big cities)
&W  may get destinations at a later time.
&R* &YAdded scriptable area resets.
&w- &WThese will allow for resets in areas to be scripted to allow a
&W  variety of things that can happen when an area resets.
&R* &YAdded two new dreaming messages.
]],
     see_also = {"task", "whereis" },
  },
  {
    keywords = {"VERSION2.6.1"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.6.1
&R* &YMade correction to Lua function to get character level
&R* &YAdded code to reload Lua states for players when there's a hotboot
&R* &YAdded functionality to Lua C code to create and rename mobs
&w- &WThis will allow for scripted resets to generate randomly named mobs
&R* &YAdded functionality to Lua C code to sset skills on players
&w- &WThis will allow tasks to give skills as rewards - for future use
&R* &YModified VERSION and TIME code
&w- &WVERSION shows HOG version
&w- &WTIME shows the time it was compiled on
&R* &YAdded command to manually restart Lua mud state.
&R* &YMoved Lua enter_room function so that the event would trigger text to
&Y  appear after the room description, items, mobs, etc...
&R* &YAdded help data to Lua C code
&w- &WThis allows Lua scripts to lookup help files that are in the original
&W  format.
&R* &YAdded Lua function to mudlib to remove skills with reimbursed practices
&w- &WThis will allow players to complete tasks that will remove skills and
&W  reimburse them with practices.
&R* &YAdded Lua function to mudlib to reward practices
&w- &WTasks can reward players with practices
&R* &YAdded Lua function to mudlib to change class and set tier
&w- &WThis was set up for future development dealing with dual-class tiers.
&R* &YCreated a new help file system using Lua
&w- &WThis new help file system utilizes catagories for each help entry. If
&W  you lookup a help on the catagories, they will automatically list all
&W  help files within that catagory that you are able to read. If there are
&W  any new help files added, they will be automatically updated upon login.
&R* &YMoved most help files into new format
&w- &WMany of the help files still need to be re-written, updated or removed.
&W  They are mainly still just the old help files output into a new format.
&W  Really the only thing different, besides the format, is that they have all
&W  been catagorized to make searching for the right help file easier.
&R* &YChanged HELP command to OLDHELP
&w- &WKeeping the old help command was necessary due to internal code being called
&W  in certain instances.
&R* &YMade new HELP command to use new Lua help file system
&R* &YRemoved NEWS command
&R* &YChanged LAWS command to use new Lua help system
&R* &YAllowed bugs to be written to log file but not bug file
&R* &YAdded Lua C code to mudlib to purge item from mob inventory
]],
    see_also = {"Lua help file system", "catagories"},
  },
  {
    keywords = {"VERSION2.6.2"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.6.2
&R* &YExtended several functions into the Lua scripting environment.
&R* &YScripted the random equipment code. Item names are no longer hard coded.
&w- &WThis has made it a lot easier to add more item names and types to the
&W  randoms code. I've added a few new metal types and several new non-metal
&W  armor types, some with a nice AC bonus. There are also new worn with pride
&W  names and some various descriptive words and phrases.
&W  As more code is extended into the scripting engine, it will not be as
&W  necessary to hardcode and recompile the mud server.
&R* &YCreated function/command to restart mud-wide Lua states as well as
&Y  individual player Lua states.
&w- &WDepending on the value of this command, I may tweak it a bit so that mortals
&W  can restart their own Lua states, without having to log out, in case something
&W  goes screwy.  
]],
  },
  {
    keywords = {"VERSION2.6.3"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.6.3
&R* &YExtended several functions into the Lua scripting environment.
&R* &YAdded ability to execute a Lua script written on a note object
&Y  from within the game. This is an implementor-only ability.
&R* &YCreated Lua functions to create new mobs from within a Lua script.
]],
  },
  {
    keywords = {"VERSION2.6.4"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.6.4
&R* &YExtended several functions into the Lua scripting environment.
&R* &YFixed a bug that disallowed new characters from accessing relevant
&Y  help files during character creation. 
&R* &YCreated Lua function to create new items from within a Lua script.
&R* &YRewrote the do_who function to use a Lua script.
]],
    see_also = {"Who"},
  },
  {
    keywords = {"VERSION2.6.5"},
    level = -1,
    htype = "version",
    text = [[
&Cv2.6.5
&R* &YMore internal code changes.
&w- &WThese changes are to make the code use up less memory by not allocating
&W  large amounts of memory that aren't necessary. This is done by reducing
&W  the number of function calls needed to produce a desired result, reducing
&W  the size of declared variables and routing other function calls through
&W  Lua functions.
&R* &YAUTOLOOT will only loot corpses that actually have items in them.
&R* &YAUTOGOLD will now gather up gold that is dropped by mobs that do not
&Y  produce a corpse.
&R* &YAll Conjurer WEAPONSMITH and ARMORSMITH spells have been tweaked.
&w- &WThese tweaks allow the spells to gain power as the conjurer gains levels.
&W  This means that the enchantments produced by these spells will yield more
&W  powerful enchants the higher the level of the conjurer.
&R* &YExperience points gained from spells will be reduced to zero (0) if you
&Y  are more than ten (10) levels higher than your victim or your victim is
&Y  another player. Experience points gained in combat are reduced in the
&Y  same fashion. You will still gain at least one (1) experience point for
&Y  killing a mob.
&R* &YMana users can no focus more mana into a spell when casting.
&w- &WSee HELP CAST for details.
]],
    see_also = {"cast"},
    },
    {
        keywords = {"VERSION2.6.6"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.6.6
&R* &YAltered log-in sequence for immortals.
&w- &WImmortals will no longer be shown the MOTD or title screens, thus skipping
&W  any 'Press Enter' screens after entering thier password.
&R* &YAreas will not reset while players are inside them. The only exception to
&Y  this is the newbie mud school area.
&w- &WThe temple section of Alden has been moved to its own area file so that
&W  players sitting around in the temple will not prevent Alden from resetting.
&R* &YIt should no longer be possible for immortals to idle out.
&R* &YMore internal changes made to help reduce the amount of memory needed to run
&Y  common functions within the game. These changes should not affect game play
&Y  and should not be apparent to players.
&R* &YImmortals are excluded from player count in areas.
&w- &WThis is to ensure that an idle, or otherwise, immortal will not prevent an
&W  area from resetting.
]],
    },
    {
        keywords = {"VERSION2.6.7"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.6.7
&R* &YMore internal tweaking.
&R* &YReplaced old ALIAS code with a Lua version.
&w- &WThis allows for a nearly unlimited number of aliases to be created. Typing
&W  ALIAS by itself will give you a list of available commands.
&R* &YAdded AFK flag to WHO output.
&R* &YFixed up the help system so it would display a possible match if the help
&Y  entry being looked for didn't exist.
&R* &YPorted the dream messages to Lua script file.
&R* &YRemoved level, magic flags, layer, rent data from objects and removed or
&Y  disabled code related to those as they are not in use.
&R* &YExpanded the number of values that can be stored in an object to allow
&Y  for future expansion.
]],
    see_also = {"alias", "alias2", "alias3", "alias variables"},
    },
    {
        keywords = {"VERSION2.7.0"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.7.0
&R* &YLots of code revolving around pets done.
&R* &YNew RESURRECT command.
&w- &WThis command is used when your pet has died and you wish to bring it
&W  back to life again.
&R* &YGroup gain tweaked for pets.
&w- &WPets will not count towards group members and will not cause a power
&W  level penalty.
&R* &YMobmaster glory awards have been tweaked.
&w- &WThis will cause a gradual increase in glory awarded as you complete
&W  more mobmasteries.
&R* &YFixed scripted resets so that mobs have a chance of popping with random
&Y  equipment.
&R* &YFixed a bug dealing with fighting in groups and using different fighting
&Y  styles.
&w- &WWhen fighting in groups, the character with the most aggressive fighting
&W  style will become the tank if they are not already.
&R* &YFixed several instances with group gains where the code was mistakenly
&Y  checking the wrong characters. I'm not certain this has affected anyone
&Y  in the past as we currently don't have very many players grouping.
&R* &YImmortals can now change bamfin and bamfout messages to not begin with
&Y  the immortals name.
&R* &YFixed a few issues with tiers not being able to use skills from their
&Y  non-tier class. These include hide, sneak and camouflage. Others may still
&Y  exist. If you find one, please notify me so that I can fix it.
&R* &YFixed an issue where a tiered character could not practice skills gained
&Y  from the non-tier class.
&R* &YHunger and thirst will now affect characters level 5 to 49 &RONLY&Y. 
&w- &WCharacters that are level 2, 3, 4, 50 or tiered will not get hungry or 
&W  thirsty. You will not lose any hp by getting hungry or thirsty, but it will 
&W  reduce your regen rate. You will get thirsty faster if you are in a desert 
&W  area and may not get thirsty as fast if you are in an underwater area.
&R* &YCharacter's mental state may be affected by drinking alcoholic liquids.
&R* &YPlayers may now train character stats up to 18 or the racial max, whichever
&Y  one is the greater value.
]],
    see_also = {"PETS", "PETSAVE", "RESURRECT", "BAMFIN", "BAMFOUT"},
    },
    {
        keywords = {"VERSION2.7.1"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.7.1
&R* &YFixed a bug that was causing players with pets to constantly have their
&Y  equipment removed when saving.
&w- &WTracked down the bug, made a mess of the code, fixed the bug, cleaned up
&W  the code. All should be good now. Don't quote me on that!
&R* &YAdded in some more safeguards for pets while I was at it.
]],
    },
    {
        keywords = {"VERSION2.7.2"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.7.2
&R* &YPets can be made to stop following by ordering them to sleep. This does
&Y  not apply to other charmed mobs.
&R* &YFixed non-bug bug that was displaying a bug message due to improper coding.
&R* &YMade some more internal changes, porting some stock functions to Lua to
&Y  clean up the code.
&R* &YPorted random magic items (potions, pills, wands, etc.) code to Lua.
]],
    },
    {
        keywords = {"VERSION2.7.3"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.7.3
&R* &YRemoved orphaned code from the source.
&w- &WThis code was no longer being used and so was a waste to compile it.
&R* &YAdded HELP VERSIONx.x.x message to TIME and VERSION command output.
&R* &YTweaks made to OSET.
&w- &WLower-level immortals with access to OSET will now have to be carrying
&W  the object they wish to oset. Higher level immortals will need to be
&W  carrying or be in the same room with the object they wish to oset. If
&W  necessary, the higher level immortal can specify an object elsewhere by
&W  prefixing the object with an exclaimation mark. This was done to prevent
&W  accidental osetting of distant objects.
&R* &YPlayers can now quit from within any safe room.
&R* &YCreated Lua scriptable invasion function.
&w- &WThis will be used to automate the holiday invasion mobs.
&R* &YCleaned up mstat code and display.
&R* &YFixed some things with the BOTTLE spell.
&R* &YFixed a bug in socials that prevented using abbreviated names.
&R* &YTweaked mobmaster code.
&w- &WMobmaster will now exclude pets. When a suitable target can't be found
&W  you will now have a variable wait time between 3 to 5 minutes instead of
&W  always waiting 5 minutes.
&R* &YModified loop routines that updates quest ticks to only check players.
&w- &WThis was previously looping through all characters in the game, including
&W  mobs. This didn't make any sense since mobs can't do quests.
&R* &YAdded color indicators to the AFFECTED command output.
]],
    },
    {
        keywords = {"VERSION2.7.4"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.7.4
&R* &YAdded Lua scripting functions to check characters for skills.
&R* &YRenamed and recoded the DRY skill to TAN.
&R* &YRecoded skill SMELT.
&R* &YCreated skill FORGE.
&R* &YCreated skill TAILOR.
&R* &YCreated skill BUTCHER.
&R* &YCreated spell DISENCHANT.
&R* &YFixed a bug with the PUT command when trying to put 'all' into a container.
&R* &YFixed crash-level bug with AQUEST/MQUEST/SQUEST INFO command.
&R* &YTweaked ARMORSMITH AVATAR.
&R* &YCreated skill CUT.
&R* &YCreated skill POLISH.
&R* &YPorted random affected_by affects to Lua script.
&w- &WThis will allow a wider variety of affects on randoms and now include aqua
&W  breath once again.
]],
    },
    {
        keywords = {"VERSION2.7.5"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.7.5
&R* &YAdded DRAINING WEAPON weapon spell.
&R* &YOpened up SQUEST and MQUEST to all classes.
&w- &WFighter classes can now do magic quests and magic classes can now do skill
&W  quests.
&R* &YAdded SHORTWHO config option.
&R* &YAdded new tokens for prompts that will display different information.
&w- &WThese are just a few new ones designed for using them in a graphical
&W  display created by a plugin for MUSHclient.
&R* &YThe AFFECTED output has been changed to show more detail about the effects
&Y  affecting you.
]],
    see_also = {"CONFIG", "PROMPT"},
	},
    {
        keywords = {"VERSION2.7.6"},
        level = -1,
        htype = "version",
        text = [[
&Cv2.7.6
&R* &YFixed a couple bugs in the FORGE skill.
]],
	},
  }
}