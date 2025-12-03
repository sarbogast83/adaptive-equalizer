set project_name "adaptive_equalizer"
open_project ./vivado/${project_name}.xpr


# run synthisis
update_compile_order -fileset sources_1
launch_runs synth_1 -jobs 11
wait_on_run synth_1
#launch_runs impl_1 -to_step write_bitstream -jobs 7
#wait_on_run impl_1

close_project