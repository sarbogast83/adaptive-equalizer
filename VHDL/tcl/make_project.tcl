set project_name "adaptive_equalizer"
create_project ${project_name} ./vivado -part xc7a100tcsg324-1 -force

set proj_dir [get_property directory [current_project]]
set obj [current_project]
 
add_files -fileset sources_1 -norecurse ./src/add16.vhd
add_files -fileset sources_1 -norecurse ./src/add32.vhd
add_files -fileset sources_1 -norecurse ./src/dff16.vhd
add_files -fileset sources_1 -norecurse ./src/dff32.vhd
add_files -fileset sources_1 -norecurse ./src/mult16.vhd
add_files -fileset sources_1 -norecurse ./src/sub16.vhd
add_files -fileset sources_1 -norecurse ./src/delayBlock.vhd
add_files -fileset sources_1 -norecurse ./src/FIRcellDF.vhd


# add_files -fileset sources_1 -norecurse ./src/

# setup IP repository path and a couple other project options 
set_property target_language VHDL [current_project]
#set_property  ip_repo_paths  ./ip_repo [current_project]
update_ip_catalog
 

close_project

 
