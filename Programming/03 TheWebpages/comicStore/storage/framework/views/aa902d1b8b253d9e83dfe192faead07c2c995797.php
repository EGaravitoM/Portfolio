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
    
    <form id="MPF" method="post">

    <ul class="GNB fixed-top">
          <li class="GNB_E inicionav"></li>
          <li class="GNB_E"><a class="" href="/"><img class="logo" src="https://bit.ly/2u7pIbu"></a></li>
          <li class="GNB_E"><a class="GNB_A" href="/">Inicio</a></li>
          <?php if(Auth::user()): ?>
          <?php if(Auth::user()->rol == 1): ?>
          <li class="GNB_E"><a class="GNB_A" href="/articulo">Crear Comic</a></li>
          <?php endif; ?>
          <?php endif; ?>
          <li class="GNB_E"><a class="GNB_A" href="/buscar">Buscar</a></li>
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

        <ul class="GNA fixed-top">
          <a href="/buscar"><h4 class="small-Title">CATEGORÍAS</h4></a>
          <li class="GNB_E"><a class="GNB_A" href="#mNew">Más Nuevo</a></li>
          <li class="GNB_E"><a class="GNB_A" href="#mVot">Más Votado</a></li>
          <?php if(!Auth::guest()): ?>
          <?php endif; ?>
        </ul>

        <div id="MC" class="container">

                <div id="carouselExampleIndicators" class="carousel slide" data-ride="carousel">
                        <ol class="carousel-indicators">
                          <li data-target="#carouselExampleIndicators" data-slide-to="0" class="active"></li>
                          
                          <li data-target="#carouselExampleIndicators" data-slide-to="Article Name"></li>
                        </ol>
                        <div class="carousel-inner">
                        <div class="carousel-item active">
                            <div class="imgcarrousel">
                              <img class="d-block w-100" src="https://bit.ly/2u7pIbu" alt="First slide">
                            </div>
                            
                            <div class="carousel-caption d-none d-md-block">
                                    <h4 class="standard">Bienvenido</h5>
                                  </div>
                          </div>
                         
                          <div class="carousel-item">
                            <div class="imgcarrousel">
                              <img class="d-block w-100" src="" alt="Nombre Comic">
                            </div>
                            
                            <div class="carousel-caption d-none d-md-block">
                                    <h4 class="standard">Nombre Comic</h5>
                                  </div>
                          </div>
                        </div>
                        <a class="carousel-control-prev" href="#carouselExampleIndicators" role="button" data-slide="prev">
                          <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                          <span class="sr-only">Previous</span>
                        </a>
                        <a class="carousel-control-next" href="#carouselExampleIndicators" role="button" data-slide="next">
                          <span class="carousel-control-next-icon" aria-hidden="true"></span>
                          <span class="sr-only">Next</span>
                        </a>
                </div>
        </div>

        

        <div class="fistA album text-muted">
          <div class="objCont">
            <h2 id="mNew">Más Nuevo</h2>
            <div class="infoProducto">
            <?php $__currentLoopData = $articles; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $articles): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
              <div class="card">
                <a href="/product/<?php echo e($articles->id); ?>"><img class="art_img" alt="100%x280" src="data:image/jpeg;base64, <?php echo e($articles->img1); ?>" data-holder-rendered="true"></a>
                <div class="card-body">
                  <h5 class="card-title">
                    <a class="standard nphl" href="/product/<?php echo e($articles->id); ?>"><?php echo e($articles->name_article); ?></a>
                  </h5>
                  <h6>$<?php echo e($articles->price); ?></h6>
                  <small>Rating: <?php echo e($articles->rating); ?></small>
                  <i class="fas fa-star"></i>
                </div>
              </div>
            <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
            </div>
          </div>
        </div>

      

        <div class="album text-muted">
          <div class="objCont">
            <h2 id="mVot">Más Votado</h2>
            <div class="infoProducto">
            <?php $__currentLoopData = $votos; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $votos): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
              <div class="card">
                <a href="/product/<?php echo e($votos->id); ?>"><img class="art_img" alt="100%x280" src="data:image/jpeg;base64, <?php echo e($votos->img1); ?>" data-holder-rendered="true"></a>
                <div class="card-body">
                  <h5 class="card-title">
                    <a class="standard nphl" href="/product/<?php echo e($votos->id); ?>"><?php echo e($votos->name_article); ?></a>
                  </h5>
                  <h6>$<?php echo e($votos->price); ?></h6>
                  <small>Rating: <?php echo e($votos->rating); ?></small>
                  <i class="fas fa-star"></i>
                </div>
              </div>
              <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
            </div>
          </div>
        </div>

        <div class="album text-muted">
          <div class="objCont">
            <h2 id="mVot">Más Caros</h2>
            <div class="infoProducto">
            <?php $__currentLoopData = $masCaros; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $masCaros): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
              <div class="card">
                <a href="/product/<?php echo e($masCaros->id); ?>"><img class="art_img" alt="100%x280" src="data:image/jpeg;base64, <?php echo e($masCaros->img1); ?>" data-holder-rendered="true"></a>
                <div class="card-body">
                  <h5 class="card-title">
                    <a class="standard nphl" href="/product/<?php echo e($masCaros->id); ?>"><?php echo e($masCaros->name_article); ?></a>
                  </h5>
                  <h6>$<?php echo e($masCaros->price); ?></h6>
                  <small>Rating: <?php echo e($masCaros->rating); ?></small>
                  <i class="fas fa-star"></i>
                </div>
              </div>
              <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
            </div>
          </div>
        </div>

        <div class="album text-muted">
          <div class="objCont">
            <h2 id="mVot">Más Baratos</h2>
            <div class="infoProducto">
            <?php $__currentLoopData = $masBaratos; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $masBaratos): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
              <div class="card">
                <a href="/product/<?php echo e($masBaratos->id); ?>"><img class="art_img" alt="100%x280" src="data:image/jpeg;base64, <?php echo e($masBaratos->img1); ?>" data-holder-rendered="true"></a>
                <div class="card-body">
                  <h5 class="card-title">
                    <a class="standard nphl" href="/product/<?php echo e($masBaratos->id); ?>"><?php echo e($masBaratos->name_article); ?></a>
                  </h5>
                  <h6>$<?php echo e($masBaratos->price); ?></h6>
                  <small>Rating: <?php echo e($masBaratos->rating); ?></small>
                  <i class="fas fa-star"></i>
                </div>
              </div>
              <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
            </div>
          </div>
        </div>

        <br>

        
        

                 <!-- <h2 id="mVis">Más Visto</h2>
                    <div class="row" th:each="articulo : ${masvisitas}">
                        <div class="card">
                            <a th:href="@{'/product/'+${articulo.IdArticulo}}"><img data-src="holder.js/100px280/thumb" alt="100%x280" style="height: 280px; width: 100%; display: block;" th:src="@{'/Imagen1/'+${articulo.IdArticulo}}" data-holder-rendered="true"></a>
                            <div class="card-body">
                            <h5 class="card-title">
                                <a th:href="@{'/product/'+${articulo.IdArticulo}}" th:text="${articulo.Nombre}"/>
                            </h5>
                            <h6 th:text="${'$ '+articulo.Precio}"/>
                            <p class="card-text_" th:text="${articulo.Descripcion}"/>
                            </div>
                            <div>
                              <small th:text="${articulo.Rating}+'/5'"/>
                              <i class="fas fa-star"></i>
                            </div>
                          </div>
                    </div>

                  <h2 id="mCal">Mejor Calificados</h2>
                  <div class="row" th:each="articulo : ${masrating}">
                      <div class="card">
                          <a th:href="@{'/product/'+${articulo.IdArticulo}}"><img data-src="holder.js/100px280/thumb" alt="100%x280" style="height: 280px; width: 100%; display: block;" th:src="@{'/Imagen1/'+${articulo.IdArticulo}}" data-holder-rendered="true"></a>
                          <div class="card-body">
                          <h5 class="card-title">
                              <a th:href="@{'/product/'+${articulo.IdArticulo}}" th:text="${articulo.Nombre}"/>
                          </h5>
                          <h6 th:text="${'$ '+articulo.Precio}"/>
                          <p class="card-text_" th:text="${articulo.Descripcion}"/>
                          </div>
                          <div>
                            <small th:text="${articulo.Rating}+'/5'"/>
                            <i class="fas fa-star"></i>
                          </div>
                        </div>
                  </div>
          -->
               


        
        


    </form>
   

</body>
</html><?php /**PATH D:\LMAD\Septimo\BDM\PF\comicStore\resources\views/index.blade.php ENDPATH**/ ?>