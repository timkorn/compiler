<html>
<head>
  <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/raphael/2.2.1/raphael.js"></script>
  <script type="text/javascript" src="../../dist/dracula.dev.js"></script>
  <script type="text/javascript" src="lib/renderer/raphael.js"></script>
  <script type="text/javascript" src="lib/renderer/snap.js"></script>
   <script type="text/javascript" src="../lib/dracula.spec.js"></script>
   <script type="text/javascript" src="../lib/dracula.js"></script>
   <script type="text/javascript" src="../lib/algorithms.js"></script>
   <script type="text/javascript" src="classes.js"></script>
   <link rel="stylesheet" href="css/style.css">
</head>
<body>
  <header><img class='logo' src="img/2.png"></header>
  <div id="canvas" style="height: 100%; width: 100%; directed"></div>
  <?php
  // Creating a PHP Array
    $fd = fopen("COM/inf.txt", 'r') or die("Error");
    $i=0;
    $my_array = array();
    while(!feof($fd))
    {
        $str1 = fgets($fd);
        $my_array[$i]=$str1;
        $i=$i+1;
    }
    fclose("COM/inf.txt");
  ?>;
  <script type="text/javascript">
         const g = new Dracula.Graph
        // Access the array elements
        var passedArray =  <?php echo json_encode($my_array); ?>;
        for(var i = 0; i < passedArray.length-1; i=i+2){
              g.addEdge(passedArray[i],passedArray[i+1])
        }
        const layouter = new Dracula.Layout.Spring(g)
        const renderer = new Dracula.Renderer.Raphael('#canvas', g, 1500, 600)
        renderer.draw()
       //var layouter = new Graph.Layout.Ordered(g, topologicalSort(g));
       //var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);
       layouter.layout();
   </script>
</body>
</html>
