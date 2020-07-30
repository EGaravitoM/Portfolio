<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class Sing_inController extends Controller
{
    public function authenticate(Request $request)
    {
        $credentials = $request->only('name', 'password');
        
        if (Auth::attempt($credentials)) {
            return redirect('/');
        }
        else{
            return redirect('/sing_in')->withErrors(['Las credenciales no coinciden', 'Las credenciales no coinciden']);;
        }
    }

    public function logout()
    {
        Auth::logout();
        return redirect(url()->previous());
    }
}
