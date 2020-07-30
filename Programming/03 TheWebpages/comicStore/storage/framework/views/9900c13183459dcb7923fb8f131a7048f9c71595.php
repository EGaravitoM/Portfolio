<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Comic Paradise Sing-In</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link href="https://fonts.googleapis.com/css?family=Palanquin&display=swap" rel="stylesheet">

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>

    <link rel="stylesheet" href="../css/reset.css">
    <link rel="stylesheet" href="../css/login.css">

</head>
<body>

   
    <form action="/login?previous=<?php echo e(URL::previous()); ?>" method="post">
        <?php echo csrf_field(); ?>

       

        <div class="login form-group">
        <?php if($errors->any()): ?>
            <h2><?php echo e($errors->first()); ?></h2>
        <?php endif; ?>
            <input class="form-control"  type="text" name="name" placeholder="Usuario" required> <br>
            <input class="form-control"  id="pass" type="password" name="password" placeholder="Contraseña" required> <br>
            <input type="checkbox" name="stay" id="staySignedIn"> Remember Me <br> <br>
            <input class="SI_E btn commonB" id="goford" type="submit" value="Ingresar">
            <input type="button"class="SI_E btn commonB" id="goback" value="Cancelar">
            <input type="button"class="SI_E btn SU commonB" id="singup" value="Registrarse">
            
        </div>

    </form>

    <script>
        $("#goback").click(function(){
            window.location.href = "/"
        });

        $("#singup").click(function(){
            window.location.href = "/sing_up"
        });
    </script>

</body>
</html><?php /**PATH D:\LMAD\Septimo\BDM\PF\comicStore\resources\views/sing_in.blade.php ENDPATH**/ ?>