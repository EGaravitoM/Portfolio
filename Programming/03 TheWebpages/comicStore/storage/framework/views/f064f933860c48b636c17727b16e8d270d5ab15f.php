<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Comic Paradise</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>

    <link rel="stylesheet" href="../css/reset.css">

    <link rel="stylesheet" href="../css/indexstyle.css">
    

</head>
<body>
    
    

    <ul class="GNB fixed-top">
          <li class="GNB_E inicionav"></li>
          <li class="GNB_E"><a class="" href="/"><img class="logo" src="https://bit.ly/2u7pIbu"></a></li>
          <li class="GNB_E"><a class="GNB_A" href="/">Inicio</a></li>
          <?php if(Auth::user()): ?>
          <?php if(Auth::user()->rol == 1): ?>
          <li class="GNB_E"><a class="GNB_A" href="/articulo">Crear Comic</a></li>
          <?php endif; ?>
          <?php endif; ?>
          <li class="GNB_E"><input class="GNB_S form-control" name="search" type="text" id="search" placeholder="Buscar">
          </li>
          <li class="GNB_E SI finnav"></li>

          <?php if(Auth::guest()): ?>
          <li class="GNB_E SI"><a class="GNB_A" href="/sing_in">Ingresar</a></li>
          <?php else: ?>
          <li class="GNB_E SI"><a class="GNB_A" href="/logout" >Salir</a></li>
          <li class="GNB_E SI"><a class="GNB_A" href="/profile/<?php echo e(Auth::user()->id); ?>" ><?php echo e(Auth::user()->name); ?></a></li>
          <li class="GNB_E SI"><img id="uimg"  src="data:image/jpeg;base64, <?php echo e(Auth::user()->user_avatar); ?>" alt=""></li>
         
            <li class="GNB_E SI"><a class="GNB_A" href="/loadCart/<?php echo e(Auth::user()->id); ?>">Carrito</a></li>
          
          <?php endif; ?>
        </ul>
        <br>
        
        <script>
            $(document).ready(function(){
              $("#search").on("keyup", function() {
                var value = $(this).val().toLowerCase();
                $(".eaf").filter(function() {
                  $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1);
                });
              });
              $(".cats").click( function() {
                var value = $(this).text().toLowerCase();
                console.log(value);
                $(".eaf").filter(function() {
                  $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1);
                });
              });
            });
        
        </script>
<br><br>
        <div style="width: 80%; margin-left:8em;">
            <?php $__currentLoopData = $cat; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $cat): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
              <small class="cats btn" value="<?php echo e($cat->name_category); ?>" ><?php echo e($cat->name_category); ?></small>
            <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
        </div>

        <div class="fistA album text-muted">
          <div class="objCont">
            <div class="infoProducto">
            <?php $__currentLoopData = $discuss; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $discuss): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
              <div class="card eaf" value="<?php echo e($discuss->name_article); ?> <?php echo e($discuss->price); ?>

                        <?php echo e($discuss->username); ?> <?php echo e($discuss->units); ?>">
                <a class="" href="/loadDiscuss/<?php echo e($discuss->id); ?>"><img class="art_img" alt="100%x280" src="data:image/jpeg;base64, <?php echo e($discuss->img1); ?>" data-holder-rendered="true"></a>
                <div class="card-body">
                  <h5 class="card-title">
                    <a class="standard nphl" href="/product/<?php echo e($discuss->article_id); ?>"><?php echo e($discuss->name_article); ?></a>
                    <a class="standard nphl" href=""><?php echo e($discuss->username); ?></a>
                  </h5>
                  <h6 class="">$<?php echo e($discuss->price); ?></h6>
                  <small class="">Unidades: <?php echo e($discuss->units); ?></small><br>
                  <i class="fas fa-star"></i>
                </div>
              </div>
              <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
            </div>
          </div>
        </div>
        theBought
        <div class="fistA album text-muted">
          <div class="objCont">
            <div class="infoProducto">
            <?php $__currentLoopData = $theBought; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $theBought): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
              <div class="card eaf" value="<?php echo e($theBought->name_article); ?> <?php echo e($theBought->price); ?>

                        <?php echo e($theBought->username); ?> <?php echo e($theBought->units); ?>">
                <a class="" href="/loadDiscuss/<?php echo e($theBought->cart_id); ?>"><img class="art_img" alt="100%x280" src="data:image/jpeg;base64, <?php echo e($theBought->img1); ?>" data-holder-rendered="true"></a>
                <div class="card-body">
                  <h5 class="card-title">
                    <a class="standard nphl" href="/product/<?php echo e($theBought->article_id); ?>"><?php echo e($theBought->name_article); ?></a>
                    <a class="standard nphl" href=""><?php echo e($theBought->username); ?></a>
                  </h5>
                  <h6 class="">$<?php echo e($theBought->price); ?></h6>
                  <small class="">Unidades: <?php echo e($theBought->units); ?></small><br>
                  <i class="fas fa-star"></i>
                </div>
              </div>
              <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
            </div>
          </div>
        </div>
           
               


        
        


    
   

</body>
</html><?php /**PATH D:\LMAD\Septimo\BDM\PF\comicStore\resources\views/adminDiscuss.blade.php ENDPATH**/ ?>