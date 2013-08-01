/* A recursive-descent parser generated by peg 0.1.9 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 19
#ifndef YY_LOCAL
#define YY_LOCAL(T)	static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)	static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)	static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)	T
#endif
#ifndef YYPARSE
#define YYPARSE		yyparse
#endif
#ifndef YYPARSEFROM
#define YYPARSEFROM	yyparsefrom
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)			\
  {							\
    int yyc= getchar();					\
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);	\
    yyprintf((stderr, "<%c>", yyc));			\
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN	( ctx->begin= ctx->pos, 1)
#endif
#ifndef YY_END
#define YY_END		( ctx->end= ctx->pos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args)	fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE	int
#endif

#ifndef YY_PART

typedef struct _yycontext yycontext;
typedef void (*yyaction)(yycontext *ctx, char *yytext, int yyleng);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

struct _yycontext {
  char     *buf;
  int       buflen;
  int       pos;
  int       limit;
  char     *text;
  int       textlen;
  int       begin;
  int       end;
  int       textmax;
  yythunk  *thunks;
  int       thunkslen;
  int       thunkpos;
  YYSTYPE   yy;
  YYSTYPE  *val;
  YYSTYPE  *vals;
  int       valslen;
#ifdef YY_CTX_MEMBERS
  YY_CTX_MEMBERS
#endif
};

#ifdef YY_CTX_LOCAL
#define YY_CTX_PARAM_	yycontext *yyctx,
#define YY_CTX_PARAM	yycontext *yyctx
#define YY_CTX_ARG_	yyctx,
#define YY_CTX_ARG	yyctx
#else
#define YY_CTX_PARAM_
#define YY_CTX_PARAM
#define YY_CTX_ARG_
#define YY_CTX_ARG
yycontext yyctx0;
yycontext *yyctx= &yyctx0;
#endif

YY_LOCAL(int) yyrefill(yycontext *ctx)
{
  int yyn;
  while (ctx->buflen - ctx->pos < 512)
    {
      ctx->buflen *= 2;
      ctx->buf= (char *)realloc(ctx->buf, ctx->buflen);
    }
  YY_INPUT((ctx->buf + ctx->pos), yyn, (ctx->buflen - ctx->pos));
  if (!yyn) return 0;
  ctx->limit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(yycontext *ctx)
{
  if (ctx->pos >= ctx->limit && !yyrefill(ctx)) return 0;
  ++ctx->pos;
  return 1;
}

YY_LOCAL(int) yymatchChar(yycontext *ctx, int c)
{
  if (ctx->pos >= ctx->limit && !yyrefill(ctx)) return 0;
  if ((unsigned char)ctx->buf[ctx->pos] == c)
    {
      ++ctx->pos;
      yyprintf((stderr, "  ok   yymatchChar(ctx, %c) @ %s\n", c, ctx->buf+ctx->pos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(ctx, %c) @ %s\n", c, ctx->buf+ctx->pos));
  return 0;
}

YY_LOCAL(int) yymatchString(yycontext *ctx, char *s)
{
  int yysav= ctx->pos;
  while (*s)
    {
      if (ctx->pos >= ctx->limit && !yyrefill(ctx)) return 0;
      if (ctx->buf[ctx->pos] != *s)
        {
          ctx->pos= yysav;
          return 0;
        }
      ++s;
      ++ctx->pos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(yycontext *ctx, unsigned char *bits)
{
  int c;
  if (ctx->pos >= ctx->limit && !yyrefill(ctx)) return 0;
  c= (unsigned char)ctx->buf[ctx->pos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++ctx->pos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", ctx->buf+ctx->pos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", ctx->buf+ctx->pos));
  return 0;
}

YY_LOCAL(void) yyDo(yycontext *ctx, yyaction action, int begin, int end)
{
  while (ctx->thunkpos >= ctx->thunkslen)
    {
      ctx->thunkslen *= 2;
      ctx->thunks= (yythunk *)realloc(ctx->thunks, sizeof(yythunk) * ctx->thunkslen);
    }
  ctx->thunks[ctx->thunkpos].begin=  begin;
  ctx->thunks[ctx->thunkpos].end=    end;
  ctx->thunks[ctx->thunkpos].action= action;
  ++ctx->thunkpos;
}

YY_LOCAL(int) yyText(yycontext *ctx, int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (ctx->textlen < (yyleng + 1))
	{
	  ctx->textlen *= 2;
	  ctx->text= (char *)realloc(ctx->text, ctx->textlen);
	}
      memcpy(ctx->text, ctx->buf + begin, yyleng);
    }
  ctx->text[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(yycontext *ctx)
{
  int pos;
  for (pos= 0;  pos < ctx->thunkpos;  ++pos)
    {
      yythunk *thunk= &ctx->thunks[pos];
      int yyleng= thunk->end ? yyText(ctx, thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, ctx->text));
      thunk->action(ctx, ctx->text, yyleng);
    }
  ctx->thunkpos= 0;
}

YY_LOCAL(void) yyCommit(yycontext *ctx)
{
  if ((ctx->limit -= ctx->pos))
    {
      memmove(ctx->buf, ctx->buf + ctx->pos, ctx->limit);
    }
  ctx->begin -= ctx->pos;
  ctx->end -= ctx->pos;
  ctx->pos= ctx->thunkpos= 0;
}

YY_LOCAL(int) yyAccept(yycontext *ctx, int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone(ctx);
      yyCommit(ctx);
    }
  return 1;
}

YY_LOCAL(void) yyPush(yycontext *ctx, char *text, int count)  { ctx->val += count; }
YY_LOCAL(void) yyPop(yycontext *ctx, char *text, int count)   { ctx->val -= count; }
YY_LOCAL(void) yySet(yycontext *ctx, char *text, int count)   { ctx->val[count]= ctx->yy; }

#endif /* YY_PART */

#define	YYACCEPT	yyAccept(ctx, yythunkpos0)

YY_RULE(int) yy_comment(yycontext *ctx); /* 19 */
YY_RULE(int) yy_contentline(yycontext *ctx); /* 18 */
YY_RULE(int) yy_whitespace(yycontext *ctx); /* 17 */
YY_RULE(int) yy_modifiers(yycontext *ctx); /* 16 */
YY_RULE(int) yy_funcargs(yycontext *ctx); /* 15 */
YY_RULE(int) yy_funcnametype(yycontext *ctx); /* 14 */
YY_RULE(int) yy_functionfooter(yycontext *ctx); /* 13 */
YY_RULE(int) yy_functionheader(yycontext *ctx); /* 12 */
YY_RULE(int) yy_EOL(yycontext *ctx); /* 11 */
YY_RULE(int) yy_linecontent(yycontext *ctx); /* 10 */
YY_RULE(int) yy_content(yycontext *ctx); /* 9 */
YY_RULE(int) yy_sectiontitle(yycontext *ctx); /* 8 */
YY_RULE(int) yy_blankline(yycontext *ctx); /* 7 */
YY_RULE(int) yy_stars(yycontext *ctx); /* 6 */
YY_RULE(int) yy_function(yycontext *ctx); /* 5 */
YY_RULE(int) yy_groupopening(yycontext *ctx); /* 4 */
YY_RULE(int) yy_comments(yycontext *ctx); /* 3 */
YY_RULE(int) yy_group(yycontext *ctx); /* 2 */
YY_RULE(int) yy_start(yycontext *ctx); /* 1 */

YY_ACTION(void) yy_1_content(yycontext *ctx, char *yytext, int yyleng)
{
#define yy ctx->yy
#define yypos ctx->pos
#define yythunkpos ctx->thunkpos
  yyprintf((stderr, "do yy_1_content\n"));
  fprintf(out, "%.*s", yyleng, yytext);;
#undef yythunkpos
#undef yypos
#undef yy
}
YY_ACTION(void) yy_1_functionheader(yycontext *ctx, char *yytext, int yyleng)
{
#define yy ctx->yy
#define yypos ctx->pos
#define yythunkpos ctx->thunkpos
  yyprintf((stderr, "do yy_1_functionheader\n"));
  printfuncheader(yytext, yyleng);;
#undef yythunkpos
#undef yypos
#undef yy
}
YY_ACTION(void) yy_1_sectiontitle(yycontext *ctx, char *yytext, int yyleng)
{
#define yy ctx->yy
#define yypos ctx->pos
#define yythunkpos ctx->thunkpos
  yyprintf((stderr, "do yy_1_sectiontitle\n"));
  
    fprintf(out, "\\section{%.*s}\n", yyleng, yytext);;
#undef yythunkpos
#undef yypos
#undef yy
}

YY_RULE(int) yy_comment(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "comment"));  if (!yymatchString(ctx, "/*")) goto l1;
  l2:;	
  {  int yypos3= ctx->pos, yythunkpos3= ctx->thunkpos;
  {  int yypos4= ctx->pos, yythunkpos4= ctx->thunkpos;  if (!yymatchString(ctx, "*/")) goto l4;  goto l3;
  l4:;	  ctx->pos= yypos4; ctx->thunkpos= yythunkpos4;
  }  if (!yymatchDot(ctx)) goto l3;  goto l2;
  l3:;	  ctx->pos= yypos3; ctx->thunkpos= yythunkpos3;
  }  if (!yymatchString(ctx, "*/")) goto l1;
  yyprintf((stderr, "  ok   %s @ %s\n", "comment", ctx->buf+ctx->pos));
  return 1;
  l1:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "comment", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_contentline(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "contentline"));  if (!yymatchString(ctx, "    ")) goto l5;  if (!yy_linecontent(ctx)) goto l5;  if (!yy_EOL(ctx)) goto l5;
  yyprintf((stderr, "  ok   %s @ %s\n", "contentline", ctx->buf+ctx->pos));
  return 1;
  l5:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "contentline", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_whitespace(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "whitespace"));
  {  int yypos9= ctx->pos, yythunkpos9= ctx->thunkpos;  if (!yymatchChar(ctx, ' ')) goto l10;  goto l9;
  l10:;	  ctx->pos= yypos9; ctx->thunkpos= yythunkpos9;  if (!yymatchChar(ctx, '\t')) goto l6;
  }
  l9:;	
  l7:;	
  {  int yypos8= ctx->pos, yythunkpos8= ctx->thunkpos;
  {  int yypos11= ctx->pos, yythunkpos11= ctx->thunkpos;  if (!yymatchChar(ctx, ' ')) goto l12;  goto l11;
  l12:;	  ctx->pos= yypos11; ctx->thunkpos= yythunkpos11;  if (!yymatchChar(ctx, '\t')) goto l8;
  }
  l11:;	  goto l7;
  l8:;	  ctx->pos= yypos8; ctx->thunkpos= yythunkpos8;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "whitespace", ctx->buf+ctx->pos));
  return 1;
  l6:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "whitespace", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_modifiers(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "modifiers"));
  {  int yypos14= ctx->pos, yythunkpos14= ctx->thunkpos;  if (!yy_whitespace(ctx)) goto l14;  goto l15;
  l14:;	  ctx->pos= yypos14; ctx->thunkpos= yythunkpos14;
  }
  l15:;	
  {  int yypos16= ctx->pos, yythunkpos16= ctx->thunkpos;  if (!yymatchString(ctx, "const")) goto l17;  goto l16;
  l17:;	  ctx->pos= yypos16; ctx->thunkpos= yythunkpos16;  if (!yymatchString(ctx, "(macro)")) goto l13;
  }
  l16:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "modifiers", ctx->buf+ctx->pos));
  return 1;
  l13:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "modifiers", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_funcargs(yycontext *ctx)
{
  yyprintf((stderr, "%s\n", "funcargs"));
  l19:;	
  {  int yypos20= ctx->pos, yythunkpos20= ctx->thunkpos;
  {  int yypos21= ctx->pos, yythunkpos21= ctx->thunkpos;  if (!yymatchChar(ctx, ')')) goto l21;  goto l20;
  l21:;	  ctx->pos= yypos21; ctx->thunkpos= yythunkpos21;
  }  if (!yymatchDot(ctx)) goto l20;  goto l19;
  l20:;	  ctx->pos= yypos20; ctx->thunkpos= yythunkpos20;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "funcargs", ctx->buf+ctx->pos));
  return 1;
}
YY_RULE(int) yy_funcnametype(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "funcnametype"));
  {  int yypos23= ctx->pos, yythunkpos23= ctx->thunkpos;  if (!yymatchChar(ctx, '*')) goto l23;  goto l22;
  l23:;	  ctx->pos= yypos23; ctx->thunkpos= yythunkpos23;
  }
  l24:;	
  {  int yypos25= ctx->pos, yythunkpos25= ctx->thunkpos;
  {  int yypos26= ctx->pos, yythunkpos26= ctx->thunkpos;  if (!yymatchChar(ctx, '(')) goto l26;  goto l25;
  l26:;	  ctx->pos= yypos26; ctx->thunkpos= yythunkpos26;
  }  if (!yymatchDot(ctx)) goto l25;  goto l24;
  l25:;	  ctx->pos= yypos25; ctx->thunkpos= yythunkpos25;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "funcnametype", ctx->buf+ctx->pos));
  return 1;
  l22:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "funcnametype", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_functionfooter(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "functionfooter"));  if (!yy_content(ctx)) goto l27;
  yyprintf((stderr, "  ok   %s @ %s\n", "functionfooter", ctx->buf+ctx->pos));
  return 1;
  l27:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "functionfooter", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_functionheader(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "functionheader"));  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_BEGIN)) goto l28;  if (!yy_funcnametype(ctx)) goto l28;  if (!yymatchChar(ctx, '(')) goto l28;  if (!yy_funcargs(ctx)) goto l28;  if (!yymatchChar(ctx, ')')) goto l28;
  {  int yypos29= ctx->pos, yythunkpos29= ctx->thunkpos;  if (!yy_modifiers(ctx)) goto l29;  goto l30;
  l29:;	  ctx->pos= yypos29; ctx->thunkpos= yythunkpos29;
  }
  l30:;	
  {  int yypos31= ctx->pos, yythunkpos31= ctx->thunkpos;  if (!yymatchChar(ctx, ';')) goto l31;  goto l32;
  l31:;	  ctx->pos= yypos31; ctx->thunkpos= yythunkpos31;
  }
  l32:;	  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_END)) goto l28;
  {  int yypos33= ctx->pos, yythunkpos33= ctx->thunkpos;  if (!yy_whitespace(ctx)) goto l33;  goto l34;
  l33:;	  ctx->pos= yypos33; ctx->thunkpos= yythunkpos33;
  }
  l34:;	  if (!yy_EOL(ctx)) goto l28;  yyDo(ctx, yy_1_functionheader, ctx->begin, ctx->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "functionheader", ctx->buf+ctx->pos));
  return 1;
  l28:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "functionheader", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_EOL(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "EOL"));
  {  int yypos36= ctx->pos, yythunkpos36= ctx->thunkpos;  if (!yymatchString(ctx, "\r\n")) goto l37;  goto l36;
  l37:;	  ctx->pos= yypos36; ctx->thunkpos= yythunkpos36;  if (!yymatchChar(ctx, '\n')) goto l38;  goto l36;
  l38:;	  ctx->pos= yypos36; ctx->thunkpos= yythunkpos36;  if (!yymatchChar(ctx, '\r')) goto l35;
  }
  l36:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "EOL", ctx->buf+ctx->pos));
  return 1;
  l35:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EOL", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_linecontent(yycontext *ctx)
{
  yyprintf((stderr, "%s\n", "linecontent"));
  l40:;	
  {  int yypos41= ctx->pos, yythunkpos41= ctx->thunkpos;
  {  int yypos42= ctx->pos, yythunkpos42= ctx->thunkpos;  if (!yy_EOL(ctx)) goto l42;  goto l41;
  l42:;	  ctx->pos= yypos42; ctx->thunkpos= yythunkpos42;
  }  if (!yymatchDot(ctx)) goto l41;  goto l40;
  l41:;	  ctx->pos= yypos41; ctx->thunkpos= yythunkpos41;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "linecontent", ctx->buf+ctx->pos));
  return 1;
}
YY_RULE(int) yy_content(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "content"));  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_BEGIN)) goto l43;
  l44:;	
  {  int yypos45= ctx->pos, yythunkpos45= ctx->thunkpos;
  {  int yypos46= ctx->pos, yythunkpos46= ctx->thunkpos;  if (!yy_contentline(ctx)) goto l47;  goto l46;
  l47:;	  ctx->pos= yypos46; ctx->thunkpos= yythunkpos46;  if (!yy_blankline(ctx)) goto l45;
  }
  l46:;	  goto l44;
  l45:;	  ctx->pos= yypos45; ctx->thunkpos= yythunkpos45;
  }  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_END)) goto l43;  yyDo(ctx, yy_1_content, ctx->begin, ctx->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "content", ctx->buf+ctx->pos));
  return 1;
  l43:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "content", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_sectiontitle(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "sectiontitle"));  if (!yymatchString(ctx, "    ")) goto l48;  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_BEGIN)) goto l48;  if (!yy_linecontent(ctx)) goto l48;  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_END)) goto l48;  if (!yy_EOL(ctx)) goto l48;  yyDo(ctx, yy_1_sectiontitle, ctx->begin, ctx->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "sectiontitle", ctx->buf+ctx->pos));
  return 1;
  l48:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "sectiontitle", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_blankline(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "blankline"));
  {  int yypos50= ctx->pos, yythunkpos50= ctx->thunkpos;  if (!yy_whitespace(ctx)) goto l50;  goto l51;
  l50:;	  ctx->pos= yypos50; ctx->thunkpos= yythunkpos50;
  }
  l51:;	  if (!yy_EOL(ctx)) goto l49;
  yyprintf((stderr, "  ok   %s @ %s\n", "blankline", ctx->buf+ctx->pos));
  return 1;
  l49:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "blankline", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_stars(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "stars"));  if (!yymatchString(ctx, "*******************************************************************************")) goto l52;  if (!yy_EOL(ctx)) goto l52;
  yyprintf((stderr, "  ok   %s @ %s\n", "stars", ctx->buf+ctx->pos));
  return 1;
  l52:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "stars", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_function(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "function"));  if (!yy_functionheader(ctx)) goto l53;
  {  int yypos54= ctx->pos, yythunkpos54= ctx->thunkpos;  if (!yy_functionfooter(ctx)) goto l54;  goto l55;
  l54:;	  ctx->pos= yypos54; ctx->thunkpos= yythunkpos54;
  }
  l55:;	
  l56:;	
  {  int yypos57= ctx->pos, yythunkpos57= ctx->thunkpos;  if (!yy_EOL(ctx)) goto l57;  goto l56;
  l57:;	  ctx->pos= yypos57; ctx->thunkpos= yythunkpos57;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "function", ctx->buf+ctx->pos));
  return 1;
  l53:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "function", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_groupopening(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "groupopening"));  if (!yy_stars(ctx)) goto l58;  if (!yy_blankline(ctx)) goto l58;  if (!yy_sectiontitle(ctx)) goto l58;  if (!yy_blankline(ctx)) goto l58;  if (!yy_content(ctx)) goto l58;  if (!yy_stars(ctx)) goto l58;
  yyprintf((stderr, "  ok   %s @ %s\n", "groupopening", ctx->buf+ctx->pos));
  return 1;
  l58:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "groupopening", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_comments(yycontext *ctx)
{
  yyprintf((stderr, "%s\n", "comments"));
  l60:;	
  {  int yypos61= ctx->pos, yythunkpos61= ctx->thunkpos;
  {  int yypos62= ctx->pos, yythunkpos62= ctx->thunkpos;  if (!yy_whitespace(ctx)) goto l63;  goto l62;
  l63:;	  ctx->pos= yypos62; ctx->thunkpos= yythunkpos62;  if (!yy_EOL(ctx)) goto l64;  goto l62;
  l64:;	  ctx->pos= yypos62; ctx->thunkpos= yythunkpos62;  if (!yy_comment(ctx)) goto l61;
  }
  l62:;	  goto l60;
  l61:;	  ctx->pos= yypos61; ctx->thunkpos= yythunkpos61;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "comments", ctx->buf+ctx->pos));
  return 1;
}
YY_RULE(int) yy_group(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "group"));  if (!yy_comments(ctx)) goto l65;  if (!yy_groupopening(ctx)) goto l65;  if (!yy_comments(ctx)) goto l65;
  l66:;	
  {  int yypos67= ctx->pos, yythunkpos67= ctx->thunkpos;  if (!yy_function(ctx)) goto l67;  goto l66;
  l67:;	  ctx->pos= yypos67; ctx->thunkpos= yythunkpos67;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "group", ctx->buf+ctx->pos));
  return 1;
  l65:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "group", ctx->buf+ctx->pos));
  return 0;
}
YY_RULE(int) yy_start(yycontext *ctx)
{
  yyprintf((stderr, "%s\n", "start"));
  l69:;	
  {  int yypos70= ctx->pos, yythunkpos70= ctx->thunkpos;  if (!yy_group(ctx)) goto l70;  goto l69;
  l70:;	  ctx->pos= yypos70; ctx->thunkpos= yythunkpos70;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "start", ctx->buf+ctx->pos));
  return 1;
}

#ifndef YY_PART

typedef int (*yyrule)(yycontext *ctx);

YY_PARSE(int) YYPARSEFROM(YY_CTX_PARAM_ yyrule yystart)
{
  int yyok;
  if (!yyctx->buflen)
    {
      yyctx->buflen= 1024;
      yyctx->buf= (char *)malloc(yyctx->buflen);
      yyctx->textlen= 1024;
      yyctx->text= (char *)malloc(yyctx->textlen);
      yyctx->thunkslen= 32;
      yyctx->thunks= (yythunk *)malloc(sizeof(yythunk) * yyctx->thunkslen);
      yyctx->valslen= 32;
      yyctx->vals= (YYSTYPE *)malloc(sizeof(YYSTYPE) * yyctx->valslen);
      yyctx->begin= yyctx->end= yyctx->pos= yyctx->limit= yyctx->thunkpos= 0;
    }
  yyctx->begin= yyctx->end= yyctx->pos;
  yyctx->thunkpos= 0;
  yyctx->val= yyctx->vals;
  yyok= yystart(yyctx);
  if (yyok) yyDone(yyctx);
  yyCommit(yyctx);
  return yyok;
}

YY_PARSE(int) YYPARSE(YY_CTX_PARAM)
{
  return YYPARSEFROM(YY_CTX_ARG_ yy_start);
}

#endif