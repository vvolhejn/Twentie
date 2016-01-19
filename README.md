# Twentie
Twentie is a Super Smash Bros. Melee AI for [Dolphin Emulator](https://github.com/dolphin-emu/dolphin). 

As it stands, the AI plays Fox and is defense-only. It knows how to:
- Recover, using jump, up-B, or side-B, depending on its position (however, it is very predictable and makes no attempt to mix up its recovery)
- Consistently perform invincible ledgedashes
- Combo DI and survival DI depending on the strength of the knockback
- Smash DI at a TAS level by making a Smash DI input every frame of hitlag. The bot will move multiple character lengths upon getting a knee to the face, for example.
- Trajectory DI in a perfectly perpendicular angle to get the best DI
- Tech nearly everything when falling to the ground (in a random direction), also attempts to tech the ground when hit by low angle attacks (aka [Amsah tech](https://youtu.be/_V4K3S5b34c?t=65)). This means the AI will survive downsmashes to ridiculous percents.

##Installation
Tested on Ubuntu 14.04. This will only work on Linux because of how Dolphin handles the communication (named pipes, Unix sockets).

1. Get Dolphin. You only need the executable, no modifications to the source are necessary.
You do need a fairly new version for this to work, though ([it must have this](https://github.com/dolphin-emu/dolphin/pull/3413)).


2. Create a named pipe in the Pipes folder of the Dolphin user directory (~/.dolphin-emu is the default) called "twentie"

    ```
    mkfifo ~/.dolphin-emu/Pipes/twentie
    ```

3. In Dolphin, go to Controllers. There, go to the GameCube Controllers configuration for port 2 (port 1 is used by the player, port 2 by the bot).
Set the device to the pipe we created (something like "Pipe/0/twentie"). It is necessary to configure this "controller" as you would with a regular one:
In Dolphin, you press the button next to "A", for example, then Dolphin waits until you make an input on your controller to associate it with the virtual GameCube button.
Of course, you don't have a controller, you have a named pipe. This means that to press A, you have to send a command to the pipe:
    ```
    echo "PRESS A" < ~/.dolphin-emu/Pipes/twentie
    ```
To see the how to make all of the input necessary, [see here](https://github.com/dolphin-emu/dolphin/blob/d9d6cf8eda0d4cd8d0350c1a4e9b5f6b708e084d/Source/Core/InputCommon/ControllerInterface/Pipes/Pipes.h).
Hopefully this step won't be required in the future.

4. Melee must have the "Netplay Community Settings" Gecko Code checked. To do this, go to Config->Enable Cheats.
Then, right click your Melee ISO, go to Properties->Gecko Codes->check "Netplay Community Settings".
This allows Melee to be at the character select screen upon startup, for example.

5. Run ```bin/Debug/Twentie``` to start the bot. Then start Melee in Dolphin. You must start the bot before Melee. 


*(Note: Because of how Dolphin reads to the named pipe, it will expect different decimal marks based on your locale (decimal point vs. decimal comma). If the bot's inputs seem strange (ex: doesn't select its character correctly), try changing the COMMAS constant in Controller.cpp and then recompiling.)*
