## Conventions

Input: Kernel -&gt; Intel

Output: Inter -&gt; Kernel


## Pre-setup phase

Happens only once, no output will be given until the AI states compatibility.

Input state current protocol version

    ROBOIME_INTEL_PROTOCOL_VERSION 1

Output state compatibility along with max compatible version

    COMPATIBLE 1

Output for future versions, if current is not supported, also state max
compatible version

    NOT_COMPATIBLE 1

If not compatible Output will EOF and the process is expected to terminate.

## Setup phase

Happens only once, right after pre-setup phase.  If geometry params change
in-game the process will be re-opened so new parameters can be loaded.

Input:

    FIELD_WIDTH
    FIELD_HEIGHT
    GOAL_WIDTH
    CENTER_CIRCLE_RADIUS
    DEFENSE_RADIUS
    DEFENSE_STRETCH
    FREE_KICK_FROM_DEFENSE_DIST
    PENALTY_SPOT_FROM_FIELD_LINE_DIST
    PENALTY_LINE_FROM_SPOT_DIST

All fields are in meters (float)


## Update phase

There are update cycles, each cycle begins with an _Input_ in which the latest state
information is sent, the core will wait for an _Update_ before going to the next
cycle.  That means that some raw updates may be skipped if the AI doesn't keep
with the pace of the Core, but that's OK though because the command are made to
have a *decent* amount of time.

The formats follow:

Input:

    TIMESTAMP
    OUR_SCORE THEIR_SCORE
    REF_STATE <REF_TIME_LEFT|-1>
    BALL_X BALL_Y BALL_VX BALL_VY
    OUR_GOALKEEPER_ID THEIR_GOALKEEPER_ID
    OUR_NUM_ROBOTS THEIR_NUM_ROBOTS
    [ROBOT_ID ROBOT_X ROBOT_Y ROBOT_W ROBOT_VX ROBOT_VY ROBOT_VW] x OUR_NUM_ROBOTS
    [ROBOT_ID ROBOT_X ROBOT_Y ROBOT_W ROBOT_VX ROBOT_VY ROBOT_VW] x THEIR_NUM_ROBOTS

- TIMESTAMP: seconds (float)
- \*\_SCORE are the scores of each team
- NUM_ROBOTS: number of robots (int)
- \*\_X and \*\_Y are positions in meters (float)
- \*\_VX and \*\_VY are velocities in meters/s (float)
- \*\_W in radians (float)
- \*\_VW in radians/s (float)
- REF_STATE: single char any of these:
  - 'H': HALT
  - 'S': STOP
  - 'N': NORMAL
  - 'p': OUR_PRE_KICKOFF
  - 'k': OUR_KICKOFF
  - 'i': OUR_INDIRECT
  - 'd': OUR_DIRECT
  - 'x': OUR_PRE_PENALTY
  - 'y': OUR_PENALTY
  - 'P': THEIR_PRE_KICKOFF
  - 'K': THEIR_KICKOFF
  - 'I': THEIR_INDIRECT
  - 'D': THEIR_DIRECT
  - 'X': THEIR_PRE_PENALTY
  - 'Y': THEIR_PENALTY
- REF_TIME_LEFT: for referee states 'kidyKIDY' this is the
  number of seconds (float) left until a fault occurs for not
  putting the ball in normal play, this will be capped to 0 if it happens to be
  less than that.  For other states it's -1 as it doesn't apply.

It's important to note that the referee is already interpreted, meaning if the
state is at NORMAL it is safe to play, no checking for opponent kick has to be
done.

On future versions the protocol may include the Z axis of the ball. Also they
may include the score, it's been left out for now.

Output:

    [ROBOT_ID <SKILL>] for each updated robot skill

_&lt;SKILL&gt;_ may be one of the skills listed in PLANNING.md
