file(REMOVE_RECURSE
  "libbinancewslib.a"
  "libbinancewslib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/binancewslib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
