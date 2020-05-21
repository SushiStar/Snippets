#Sampling-based approaches
No preprocessing step: starting with the initial configuration $q_1$ build the graph (actually, tree) until the goal configuration $g_G$ is part of it.

###RRT
<p float="center">
    <img src="/Users/waynedu/Snippets/planning_scripts/figures/RRTAlg.png" alt="RRT Algorithm" width="370"/> 
    <img src="/Users/waynedu/Snippets/planning_scripts/figures/RRTAlgExplain.png" alt="RRT Algorithm Explained" width="350"/>
</p>

###RRT-Connect
<p float="left">
    <img src="/Users/waynedu/Snippets/planning_scripts/figures/RRTConnect.png" alt="RRT Algorithm" width="400"/> 
</p>

###PRMs vs. RRTs
- PRMs construct a roadmap and then searches it for a solution whenever $q_I, g_G$ are given. Well suited for repeated planning in between different pairs of $q_I, g_G$ (multiple queries)
- RRTs construct a tree for a given $q_I, g_G$ until the tree has a solution. Well suited for single-shot planning in between a single pair of $q_I, g_G$ (single queyr). There exists extensions of RRTs that try to reuse a previously constructed tree when replanning in response to map updates

###RRT*
Re-wiring: Checking if we can improve (re-wire) the cost of other nodes near the new node $x_{new}$.
<p float="center">
    <img src="/Users/waynedu/Snippets/planning_scripts/figures/RRTStar1.png" alt="RRT Algorithm" width="400"/> 
    <img src="/Users/waynedu/Snippets/planning_scripts/figures/RRTStar2.png" alt="RRT Algorithm Explained" width="380"/>
</p>


