#encoding "utf-8"    // сообщаем парсеру о том, в какой кодировке написана грамматика
#GRAMMAR_ROOT S      // указываем корневой нетерминал грамматики

Chto -> Word+ ',' 'что';
S-> Chto interp (Desc.LeftText::not_norm) Noun interp (Desc.Main::not_norm) Word+ interp (Desc.RightText::not_norm);

AdjCoord -> Adj;                                      // вырожденный случай, когда цепочка пригалательных - однородных членов
AdjCoord -> Word<gram="A, brev">;

AdjCoord -> AdjCoord<gnc-agr[1]> ',' Adj<gnc-agr[1]>; // пригалательные - однородные члены могут быть записаны через запятую
AdjCoord -> AdjCoord<gnc-agr[1]> 'и' Adj<gnc-agr[1]>; // или через сочинительный союз 'и'
AdjCoord -> 'на' Adj | 'без' Adj | 'не' Adj;
AdjCoord -> Noun<gnc-agr[1]> Adj<gnc-agr[1]>; 
//brev


LeftAdj -> AdjCoord+ Word*;
RightAdj -> Word* AdjCoord+;

Cheres -> 'Через' AnyWord+;
// S -> Cheres interp (Desc.LeftText::not_norm) Noun interp (Desc.Main::not_norm) RightAdj interp (Desc.RightText::not_norm);

S -> Noun<rt>+ interp (Desc.Main::not_norm) RightAdj interp (Desc.RightText::not_norm);
S -> LeftAdj interp (Desc.LeftText::not_norm) Noun<rt>+ interp (Desc.Main::not_norm);
S -> Word<rt, gram="partcp">+ interp (Desc.Main::not_norm) RightAdj interp (Desc.RightText::not_norm);
S -> LeftAdj interp (Desc.LeftText::not_norm) Word<rt, gram="partcp">+ interp (Desc.Main::not_norm);


VerbCoord -> Verb+;                                      // вырожденный случай, когда цепочка пригалательных - однородных членов
//                                                       // состоит из одного прилагательного
VerbCoord -> VerbCoord<gnc-agr[1]> ',' Verb<gnc-agr[1]>; // пригалательные - однородные члены могут быть записаны через запятую
VerbCoord -> VerbCoord<gnc-agr[1]> 'и' Verb<gnc-agr[1]>; // или через сочинительный союз 'и'
VerbCoord -> 'на' Verb | 'без' Verb | 'не' Verb;

VerbCoord -> Noun Verb;

LeftVerb -> VerbCoord+ Word*;
RightVerb -> Word* VerbCoord+;

S -> LeftVerb interp (Desc.LeftText::not_norm) Noun+ interp (Desc.Main::not_norm);
S -> Noun+ interp (Desc.Main::not_norm) RightVerb interp (Desc.RightText::not_norm);


AdvCoord -> Adv+;                                      // вырожденный случай, когда цепочка пригалательных - однородных членов
                                                      // состоит из одного прилагательного
AdvCoord -> AdvCoord<gnc-agr[1]> ',' Adv<gnc-agr[1]>; // пригалательные - однородные члены могут быть записаны через запятую
AdvCoord -> AdvCoord<gnc-agr[1]> 'и' Adv<gnc-agr[1]>; // или через сочинительный союз 'и'
AdvCoord -> 'на' Adv | 'без' Adv | 'не' Adv;

LeftAdv -> AdvCoord+ Word*;
RightAdv -> Word* AdvCoord+;

S -> Noun+ interp (Desc.Main::not_norm) RightAdv interp (Desc.RightText::not_norm);
S -> LeftAdv interp (Desc.LeftText::not_norm) Noun+ interp (Desc.Main::not_norm);

S -> Word<rt, gram="partcp">+ interp (Desc.Main::not_norm) RightAdv interp (Desc.RightText::not_norm);
S -> LeftAdv interp (Desc.LeftText::not_norm) Word<rt, gram="partcp">+ interp (Desc.Main::not_norm);



NotWord -> 'не' Word;
S-> Noun interp (Desc.Main::not_norm) NotWord interp (Desc.RightText::not_norm);
S-> NotWord interp (Desc.RightText::not_norm) Noun interp (Desc.Main::not_norm);