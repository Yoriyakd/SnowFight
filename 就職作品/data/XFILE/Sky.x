xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Cube {
    FrameTransformMatrix {
      499.999756, 0.000000, 0.000000, 0.000000,
       0.000000,499.999756, 0.000000, 0.000000,
       0.000000, 0.000000,500.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Cube mesh
      24;
       1.000000; 1.000000;-1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000;-1.000000;-1.000000;,
       1.000000;-1.000000;-1.000000;,
       1.000000; 0.999999; 1.000000;,
       0.999999;-1.000001; 1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000; 1.000000; 1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000;-1.000000;-1.000000;,
       0.999999;-1.000001; 1.000000;,
       1.000000; 0.999999; 1.000000;,
       1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000; 1.000000;,
       0.999999;-1.000001; 1.000000;,
      -1.000000;-1.000000;-1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000; 1.000000; 1.000000;,
      -1.000000;-1.000000; 1.000000;,
       1.000000; 0.999999; 1.000000;,
      -1.000000; 1.000000; 1.000000;,
      -1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000;-1.000000;;
      6;
      4;3,2,1,0;,
      4;7,6,5,4;,
      4;11,10,9,8;,
      4;15,14,13,12;,
      4;19,18,17,16;,
      4;23,22,21,20;;
      MeshNormals { // Cube normals
        6;
         0.000000;-0.000000; 1.000000;,
         0.000000; 0.000000;-1.000000;,
        -1.000000; 0.000000;-0.000000;,
         0.000000; 1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
        -0.000000;-1.000000;-0.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube normals
      MeshTextureCoords { // Cube UV coordinates
        24;
         0.499482; 0.999915;,
         0.249269; 0.999682;,
         0.249957; 0.663581;,
         0.499575; 0.667018;,
         0.495348; 0.006887;,
         0.497679; 0.339013;,
         0.251594; 0.337729;,
         0.253438; 0.005386;,
         0.750032; 0.666850;,
         0.499575; 0.667018;,
         0.497679; 0.339013;,
         0.750059; 0.338366;,
         0.499575; 0.667018;,
         0.249957; 0.663581;,
         0.251594; 0.337729;,
         0.497679; 0.339013;,
         0.249957; 0.663581;,
         0.000970; 0.663582;,
         0.001602; 0.336461;,
         0.251594; 0.337729;,
         0.750059; 0.338366;,
         0.999997; 0.338239;,
         0.999951; 0.666971;,
         0.750032; 0.666850;;
      } // End of Cube UV coordinates
      MeshMaterialList { // Cube material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material {
           0.640000; 0.640000; 0.640000; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"data/Texture/Sky.png";}
        }
      } // End of Cube material list
    } // End of Cube mesh
  } // End of Cube
} // End of Root
