set project_name "adaptive_equalizer"
create_project ${project_name} ./vivado -part xc7a100tcsg324-1 -force

set proj_dir [get_property directory [current_project]]
set obj [current_project]

# add all files from src
add_files -fileset sources_1 [glob ./src/*.vhd] 

# add_files -fileset sim_1 ./src/AE_topTestbench.vhd

# add_files -fileset sources_1 -norecurse ./src/

# setup IP repository path and a couple other project options 
set_property target_language VHDL [current_project]
#set_property  ip_repo_paths  ./ip_repo [current_project]
update_ip_catalog
 

close_project

 
