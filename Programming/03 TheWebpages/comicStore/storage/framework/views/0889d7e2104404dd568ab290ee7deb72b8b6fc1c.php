<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Producto</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">

    <link rel="stylesheet" href="../css/reset.css">
    <link rel="stylesheet" href="../css/product.css">
    <link rel="stylesheet" href="../css/navbar.css">

   <script src="../js/starrr.js"></script>
    

    
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

        <h1 id="ndp" value="" ><?php echo e($article->name_article); ?></h1>
        <?php if(Auth::user()): ?>
        <?php if(Auth::user()->rol == 1): ?>
        <a class="btn commonB" href="/loadDiscussAdmin">Discusion</a>
        <?php endif; ?>
        <?php endif; ?>
        <div id="imgs">
            <div id="imgMain" class="container">
                <img id="main" src="data:image/jpeg;base64, <?php echo e($article->img1); ?>" alt="Imagen no Encontrada">
            </div>
            <div id="ImgMuestra" class="container">
                <img id="top" src="data:image/jpeg;base64, <?php echo e($article->img2); ?>" alt="img2 n/e">
            </div>
            <div id="ImgMuestra2" class="container">
                <img id="top" src="data:image/jpeg;base64, <?php echo e($article->img3); ?>" alt="img3 n/e">
            </div>
        </div>

        
        <div class="descpres">
            <div class="descripcion">
                <p id="info" class="des cripcion" value="" ><?php echo e($article->description_article); ?></p>   
            </div>
            <div id="percio_unidades">
                Precio: <b><span value="">$<?php echo e($article->price); ?></span></b><br>
                Unidades: <b><span value="" ><?php echo e($article->units); ?></span></b><br>
                Categoría: <b><span><?php echo e($article->name_category); ?></span></b>
                <div id="casaEstrellas">
                Rating: <span id="Estrellas" value="" ><b><?php echo e($rating->rating); ?></b></span> 
                    
                    <?php if(!Auth::guest()): ?>
                    <?php if($hasBought[0]->answer): ?>
                    <form id="rateo" method="get" action="/updateRates">
                        <?php echo csrf_field(); ?>
                        <button class="estrellita star_b" value="1" id="primero"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="2" id="segundo"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="3" id="tercero"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="4" id="cuarto"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <button class="estrellita star_b" value="5" id="quinto"><img  src="https://img.icons8.com/metro/26/000000/star.png"></button>
                        <input type="hidden" id="goodStar" name="valorRating" value="">
                        <input type="hidden" id="idcar" name="article_id" value="<?php echo e($article->id); ?>">

                        <script>

                            $(document).ready(function(){
                                $('.estrellita').on('mouseenter', function(){
                                    var index = $(this).index();
                                    var tmpindex = 0;
                                    $('.estrellita').each(function(sindex){
                                        if(sindex < index){
                                            $(this).addClass('star_y');
                                            $(this).removeClass('star_b');
                                        }
                                        else{
                                            $(this).addClass('star_b');
                                            $(this).removeClass('star_y');
                                        }
                                    });
                                });

                                $(".estrellita").click(function(){
                                    $("#goodStar").val($(this).val());
                                    $("#rateo").submit();
                                });
                            });

                        </script>
                       <!-- <label for="#segundo"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="4" id="segundo">
                        <label for="#tercero"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="3" id="tercero">
                        <label for="#cuarto"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="2" id="cuarto">
                        <label for="#quinto"><img src="https://img.icons8.com/metro/26/000000/star.png"></label>
                        <input type="submit" class="estrellita" name="star" value="1" id="quinto"> -->
                    </form>
                    <?php endif; ?>
                    <?php endif; ?>
                    
                    <br>
                </div>
            </div>
        </div>
        <div class="compra_fav container">

            <form method="post" action="/addCart">
            <?php echo csrf_field(); ?>
                <div class="container form-group" id="amount">
                    <label for="#units">Selecciona las que Quieras</label>
                    <input type="number" name="unit" class="form-control"  min="1" id="units" required>
                    <input type="hidden" name="article_id" value="<?php echo e($article->id); ?>">
                    <?php if(Auth::user()): ?>
                    <input type="hidden" name="user_id" value="<?php echo e(Auth::user()->id); ?>">
                    <?php endif; ?>
                    <br>
                    <input type="hidden" name="creatorId" value="" required>
                    <input type="hidden" name="articleId" value="" required>
                    <?php if(Auth::guest()): ?>
                        <a id="ATC" class="btn commonB" href="/sing_in">Añadir al Carrito</a>
                    <?php else: ?>
                        <input type="submit" id="ATC" class="btn commonB" value="Añadir al Carrito">
                    <?php endif; ?>
                    
                </div>
            </form>

        </div>

    <div class="video container">
        <video style="align-self: center" src="../images/<?php echo e($article->video); ?>" controls></video>
        </div>
        
    
   

    <form method="post" action="/generateComment/<?php echo e($article->id); ?>">
        <?php echo csrf_field(); ?>
        <div class="container form-group comentgroup">
            <?php if(Auth::guest()): ?>
                <textarea placeholder="Añade un comentario..." name="coments" id="cbox" cols="150" rows="3"></textarea>
                <a id="bc2" class="btn commonB" href="/sing_in">Comentar</a>
            <?php else: ?>
                
                    <textarea placeholder="Añade un comentario..." name="coments" id="cbox" cols="150" rows="3" required></textarea>
                
                <?php if($hasBought[0]->answer): ?>
                    <input type="submit" id="bc2" class="btn commonB" value="Comentar">
                <?php else: ?>
                    <button id="bc2" class="btn commonB">No puedes comentar hasta comprar</button>
                <?php endif; ?>
                
            <?php endif; ?>
    </form>
            <!-- 
            th:field="" -->
            <br>
            <br>
            <br>
            <br>
        
            <h2>Comentarios</h2>
            <div class="comentario row" >
            <?php $__currentLoopData = $comments; $__env->addLoop($__currentLoopData); foreach($__currentLoopData as $comments): $__env->incrementLoopIndices(); $loop = $__env->getLastLoop(); ?>
                <div class="us_img" >
                    <a href="" ><b><?php echo e($comments->name); ?></b></a>
                    <div class="imgcomment">
                        <a><img src="data:image/jpeg;base64, <?php echo e($comments->user_avatar); ?>"  alt="100%x280" data-holder-rendered="true"></a>
                    </div>
                </div>
                <div class="u_commen">
                    <p><?php echo e($comments->comment_content); ?></p>
                </div>
                <div>
                    <p><?php echo e($comments->created_at); ?></p>
                </div>
                <?php endforeach; $__env->popLoop(); $loop = $__env->getLastLoop(); ?>
            </div>
<!--th:src="@{'/Imagen1/'+${allcomens.idUser}}"-->
        </div>
        
    

    <script>

    </script>

</body>
</html><?php /**PATH D:\LMAD\Septimo\BDM\PF\comicStore\resources\views/product.blade.php ENDPATH**/ ?>