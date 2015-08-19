# Software 2016 Project Planning

```
               --------------------
               | SSL-VISION | REF |      -------
               --------------------   /--| SIM |
                     |         |      |  -------
                     |         |      |     |
                     |         |      |     |
                    \|/       \|/    \|/    |
 -----------      ------------------------  |
 |         |      |                      |  |
 |         |<-----|        KERNEL        |  |      ^
 |  INTEL  |      |                      |  |      |
 |         |      ------------------------  |   ------
 |         |----->|        CONTROL       |----->| TX |
 -----------      ------------------------      ------
```

## Modules

- Kernel
  - Control (multithread)
- Tx
- Sim (independent process)
- Intel (independent process)

## Composition

### Kernel

- Vision treatment
- Game State
  - Vision data
  - Referee state
- Intel I/O
- Logging
- Profiling

### Control

- PID / Omni equation
- Path Planning
- Transmission

## Implementation

### Kernel

- Skills
  - type : SkillType enum
  - skillParams : union
    - target
      - position : Vector2
      - area : float
    - robotId : unsigned char
    - kick
      - forceKick : bool (default: false)
      - forceChip : bool (default: false)
      - kickForce : unsigned char

- Game State
  - refereeState : RefereeState enum
  - gameTime : float

  - World
    - Field Params
      - _all field parameters_
    - ball : Ball
      - position : Vector2 (Vector3?)
      - velocity : Vector2 (Vector3?)
      - positionError? : Vector2 (Vector3?)
      - velocityError? : Vector2 (Vector3?)
      - (radius? : float)
    - robots : Robot vector
      - team : Team enum (Yellow or Blue) (bool?)
      - position : Vector2 (Vector3?)
      - velocity : Vector2 (Vector3?)
      - positionError? : Vector2 (Vector3?)
      - velocityError? : Vector2 (Vector3?)
      - orientation/angle : float
      - angularVelocity : float
      - skill: Skill
      - (radius? : float)
    - Teams
      - name? : string
      - score : int

- Profiler
- Logger

### Control

- ?

## Skills

### Basic skills

- **goto &lt;pos&gt;**

  Robot goes to position looking at the ball.

- **gotoball [kick]**

  Robot follows the ball and, if kick flag is set, kicks as soon as it touches
  the the ball.

- **kick &lt;pos&gt;**

  Robot goes to the ball, orients to _pos_ and kicks as soon as the angles is
  good enough.

- **wait**

  Robots stays in place and does nothing (doesn't even look at the ball).

### Future skills

- **chip &lt;pos&gt;**

  Same as _kick_, but the robots chip kicks.

- **pass &lt;id&gt;**

  Robot goes to the ball and kicks in the direction of another robot on the same
  team with the chosen _id_.

- **mark &lt;id&gt;**

  _To be defined_.

- **deflect &lt;pos&gt; &lt;target&gt;**

  Robot positions in _pos_ and orients so that he can deflect an incoming ball
  to the _target_ position. Kicks as soon as the ball hits the robot.
