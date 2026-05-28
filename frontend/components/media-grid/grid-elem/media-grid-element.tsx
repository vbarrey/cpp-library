import { motion } from "motion/react";

import { Book, Game, Movie, Series } from "@/lib/api";

import { BookContent } from "./book-content";
import { GameContent } from "./game-content";
import { MovieContent } from "./movie-content";
import { SeriesContent } from "./series-content";

import { GridItemLayout } from "../layout";
import { Movie as G_Movie } from "@/graphql/generated/graphql";

type Props = {
    media: G_Movie;
    layout: GridItemLayout;
    expanded: boolean;
    
    shouldAnimateSize: boolean;
    isTransitioning: boolean;
    isAnimatingLayout: boolean;

    scrollTarget: React.RefObject<HTMLElement | null>;

    setTransitioningIds: (ids: Set<string>) => void;
    setIsAnimatingLayout: (value: boolean) => void;

    handleClick: (target: HTMLElement, mediaId: string) => void;
};

export function MediaGridElement({ media, layout, expanded, shouldAnimateSize, isTransitioning, isAnimatingLayout, scrollTarget, setTransitioningIds, setIsAnimatingLayout, handleClick }: Props) {
    return (
        <motion.div
            key={media.id}

            layout={shouldAnimateSize ? true : "position"}

            transition={{
                layout: {
                    duration: 0.45,
                    ease: "easeInOut",
                }
            }}

            onLayoutAnimationComplete={() => {

                if (!isAnimatingLayout) {
                    return;
                }

                setIsAnimatingLayout(false);

                setTransitioningIds(
                    new Set()
                );

                scrollTarget.current?.scrollIntoView({
                    behavior: "smooth",
                    block: "center"
                });

            }}

            style={{
                gridColumn:
                    `${layout.col} / span ${layout.colSpan}`,

                gridRow:
                    `${layout.row} / span ${layout.rowSpan}`,
            }}

            onClick={(e) => {
                handleClick(e.currentTarget, media.id);
            }}

            className="
                            rounded-2xl
                            border
                            bg-card
                            overflow-hidden
                            cursor-pointer
                            shadow-sm
                        "
        >

            {/* CONTENU ANIMÉ */}

            <motion.div
                animate={{
                    opacity:
                        isTransitioning
                            ? 0
                            : 1,

                    filter:
                        isTransitioning
                            ? "blur(6px)"
                            : "blur(0px)",
                }}

                transition={{
                    duration: 0.15,
                }}

                className="
                                h-full
                            "
            >

                <div className="flex h-full">

                    {/* COVER */}

                    <div
                        className="
                                        shrink-0
                                        overflow-hidden
                                        aspect-[2/3]
                                        h-full
                                    "
                    >

                        <img
                            src={media.coverUrl || ""}
                            alt={media.title}
                            className="
                                            w-full
                                            h-full
                                            object-cover
                                        "
                        />

                    </div>

                    {/* SPECIFIC CONTENT */}

                    {media.type === "BOOK" && <BookContent book={media as Book} expanded={expanded} />}
                    {media.type === "MOVIE" && <MovieContent movie={media as Movie} expanded={expanded} />}
                    {media.type === "GAME" && <GameContent game={media as Game} expanded={expanded} />}
                    {media.type === "SERIES" && <SeriesContent series={media as Series} expanded={expanded} />}

                </div>

            </motion.div>

        </motion.div>
    );
}