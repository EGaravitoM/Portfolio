<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Articulo</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    
    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>

    <link rel="stylesheet" href="../css/reset.css">
    <link rel="stylesheet" href="../css/navbar.css">
    <link rel="stylesheet" href="../css/addart.css">

</head>
<body style="padding-left: 5%; padding-top: 50px">

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

    <div class="container">
        
        <form action="/articleMake" method="post" enctype="multipart/form-data">
            <?php echo csrf_field(); ?>

                <div class="form-group">
                    <label for="itemname">Nombre</label>
                    <input type="text" class="form-control" name="name_article" id="itemname" placeholder="Nombre" required />
                    <small id="itemnameHelp" class="form-text text-muted">Nombre producto</small>
                </div>
                <div class="form-group">
                    <label for="descripcion">Descripción</label>
                    <textarea style="font-color=black" name="description_article" id="descripcion" cols="75" rows="10"></textarea>
                    <small id="descripcionHelp" class="form-text text-muted">Descripcion breve del producto.</small>
                </div>
                <div class="form-group">
                    <label for="">Categorias del Producto</label>
                    <select multiple class="form-control" name="comicCategoria" id="" required>
                        <option value="1">Acción</option>
                        <option value="2">Fantasía</option>
                        <option value="3">Indie</option>
                        <option value="4">Sci-fi</option>
                        <option value="5">Drama</option>
                    </select>
                </div>
                <div class="form-group">
                    <label for="price">Precio</label>
                    <input type="number" min="1" name="price" class="form-control" id="price" placeholder="Precio" required>
                    <small id="priceHelp" class="form-text text-muted">Costo del producto.</small>
                </div>
                <div class="form-group">
                    <label for="units">Unidades</label>
                    <input type="number" min="1" name="units" class="form-control" id="units" placeholder="Unidades" required>
                    <small id="unitsHelp" class="form-text text-muted">Total de Unidades.</small>
                </div>
                <div class="form-group">
                    <label for="img1">Imagen1</label><br>
                    <input type="file" name="comicImg1" id="img1" required>
                    <small id="img1Help" class="form-text text-muted">Extra points for originality</small>
                </div>
                <div class="form-group">
                    <label for="img2">Imagen2</label><br>
                    <input type="file" name="comicImg2" id="img2" required>
                    <small id="img2Help" class="form-text text-muted">Extra points for originality</small>
                </div>  

                <div class="form-group">
                    <label for="img3">Imagen3</label><br>
                    <input type="file" name="comicImg3" id="img3" required>
                    <small id="img3Help" class="form-text text-muted">Extra points for originality</small>
                </div>

                <div class="form-group">
                    <label for="video">Video</label><br>
                    <input type="file" name="comicvideo" id="video" required>
                    <small id="videoHelp" class="form-text text-muted">Extra points for originality</small>
                </div> 

                <button id="go" type="submit" class="btn commonB" style="float: right;">Crear</button>
                <button id="nogo" type="reset" class="btn commonB" style="float: left;">Cancelar</button>
                </div>
        </form>

</div>


    <script>
        $("#nogo").click(function(){
            window.location.href = "/";
        });

    </script>

</body>
</html><?php /**PATH D:\LMAD\Septimo\BDM\PF\comicStore\resources\views/articulo.blade.php ENDPATH**/ ?>