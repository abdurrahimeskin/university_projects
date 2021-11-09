#lang scheme
;2016400387

 
;---------------------------------------------------------------PROBLEM 3.1 SOLUTIONS----------------------------------------------- 

;RAILWAY-CONNECTION:

;I create a list and look the neighbor location by controlling that list

(define (connection city connectionlist) (if(equal? null connectionlist) null

                            (if(equal? city (car (car connectionlist))) (caddr (car connectionlist)) (connection city (cdr connectionlist)))))

 

(define (RAILWAY-CONNECTION city) (connection city LOCATIONS))

 

 

;ACCOMMODATION-COST

;ı keep the accomodation costs in list and call that information

(define (accommodation city accommodationlist) (if (equal? null accommodationlist) null

                             (if(equal? city (car (car accommodationlist))) (cadr(car accommodationlist)) (accommodation city (cdr accommodationlist)))))

 

(define (ACCOMMODATION-COST city) (accommodation city LOCATIONS))

 

 

;INTERESTED-ACTIVITIES

;ı keep the infromation of the person in list that he or she interested in and controlled and get them when they called

(define (activities person activitylist) (if (equal? null activitylist) null

                               (if(equal? person (car (car activitylist))) (caddr(car activitylist)) (activities person (cdr activitylist)) )))

 

(define (INTERESTED-ACTIVITIES person) (activities person TRAVELERS))

 

 

;INTERESTED-CITIES

;for that case i use the same mechanism for a person to find which cities interested in

(define (cities person citylists) (if (equal? null citylists) null

                               (if(equal? person (car (car citylists))) (cadr(car citylists)) (cities person (cdr citylists)) )))

 

(define (INTERESTED-CITIES person) (cities person TRAVELERS))

 

 

;HOME:

;I use a list again and to find home informations i conterolled that list 

(define (home person homelist) (if(equal? null homelist) null

                               (if(equal? person (car (car homelist))) (cadddr(car homelist)) (home person (cdr homelist) ) )))

 

(define (HOME person) (home person TRAVELERS))

 

;---------------------------------------PROBLEM 3.2 SOLUTIONS-------------------------------------------------- 
 
;TRAVELER-FROM

; I used a list and returned a list involving the travelers whose hometown is that location

(define (travelplace city travelist)

      (if (equal? null travelist)

          null

          (if (equal? city  (cadddr (car travelist)))

              (cons (caar travelist) (travelplace city (cdr travelist)))

              (travelplace city (cdr travelist)))))

             

              

(define (TRAVELER-FROM city) (travelplace city TRAVELERS))

 

 

 

 

 

;INTERESTED-IN-CITY:

;ı kept all information of people for cities which are interested in 

(define (interestedcities city interestedcitieslist) (if(equal? null interestedcitieslist) null

                                    (if(equal? city (car interestedcitieslist))

                                       #t

                                       (interestedcities city (cdr interestedcitieslist))

                                       ) ))

 

(define (interestedcities1 city interestedcitieslist2) (if(equal? null interestedcitieslist2) null

                               (if (eq? #t (interestedcities city (cadr (car interestedcitieslist2))))

                                   (cons (caar interestedcitieslist2) (interestedcities1 city (cdr interestedcitieslist2)))

                                   (interestedcities1 city (cdr interestedcitieslist2))

                                   )

                               ))

 

 

(define (INTERESTED-IN-CITY city) (interestedcities1 city TRAVELERS))

 

 

 

;INTERESTED-IN-ACTIVITY:

;ı kept all information of people for activities which are interested in

(define (interestedactivities act interestedactivitieslist) (if(equal? null interestedactivitieslist) null

                                    (if(equal? act (car interestedactivitieslist))

                                       #t

                                       (interestedactivities act (cdr interestedactivitieslist))

                                       ) ))

 

(define (interestedactivities1 act interestedactivitieslist2) (if(equal? null interestedactivitieslist2) null

                               (if (eq? #t (interestedactivities act (caddr (car interestedactivitieslist2))))

                                   (cons (caar interestedactivitieslist2) (interestedactivities1 act (cdr interestedactivitieslist2)))

                                   (interestedactivities1 act (cdr interestedactivitieslist2))

                                   )

                               ))

 

(define (INTERESTED-IN-ACTIVITY act) (interestedactivities1 act TRAVELERS))

 

 

 
;---------------------------------------PROBLEM 3.3 SOLUTIONS-------------------------------------------------- 
 

;RAILWAY-NETWORK:

;ı controlled all points of locations from every locations which can be reached by train.


(define (RAILWAY-NETWORK city)  (networinformation (RAILWAY-CONNECTION city) city))

 

(define (listsummation citylist citylist2 city)

  (if (eqv? citylist2 null) citylist 

      (if (or(memv (car citylist2) citylist) (equal? (car citylist2) city))

          (listsummation citylist (cdr citylist2) city)

            (listsummation (cons (car citylist2) citylist) (cdr citylist2) city))))

 

 

(define(networkhelp helplist city)

  (if (eqv? helplist null) null

      (listsummation (listsummation helplist (RAILWAY-CONNECTION (car helplist)) city) (networkhelp (cdr helplist ) city) city)))

 

(define (networinformation list city)     (if(equal? (length list) (length(networkhelp list city)))

                                       list

                                      (networinformation (networkhelp list city) city)

                                      ))

 

 

 ;---------------------------------------PROBLEM 3.4 SOLUTIONS-------------------------------------------------- 

;ACCOMMODATION-EXPENSES:

;I calculated accomodation expenses for each travellers


(define (aexpense person city ) (if(equal? city (HOME person))
                                   0
                                   (if(memq city (INTERESTED-CITIES person))
                                      (* 3 (ACCOMMODATION-COST city))
                                      (ACCOMMODATION-COST city)
                                      )
                                   ))

(define (ACCOMMODATION-EXPENSES person city) (aexpense person city))



;TRAVEL-EXPENSES:

; I calculated all travel expenses


(define (texpense person city) (if(equal? city (HOME person))
                                  0
                                (if(memq city (RAILWAY-NETWORK (HOME person)))
                                   100
                                   200
                                   )))

(define (TRAVEL-EXPENSES person city) (texpense person city))





;EXPENSES

; I have calculated all expenses for each travellers


(define (totalexpense person city) (+ (TRAVEL-EXPENSES person city) (ACCOMMODATION-EXPENSES person city) ))



(define (EXPENSES person city) (totalexpense person city))



;---------------------------------------PROBLEM 3.5 SOLUTIONS-------------------------------------------------- 


;IN_BETWEEN


;I controlled the accomodation cost price for locations for looking is it in the threshold or not

(define (betweensituation I B locatıons) (if(equal? null locatıons) null

                                    (

                                     if(and (>= (cadr (car locatıons)) I) (<= (cadr (car locatıons)) B))

                                       (cons (car(car locatıons)) (betweensituation I B (cdr locatıons)))

                                       (betweensituation I B (cdr locatıons))

                                       )

                                    ) )

 

 

(define (IN_BETWEEN I B) (betweensituation I B LOCATIONS) )

