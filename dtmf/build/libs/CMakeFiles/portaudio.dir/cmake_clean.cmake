file(REMOVE_RECURSE
  "libportaudio.a"
  "libportaudio.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/portaudio.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
